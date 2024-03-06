#include "ring.hpp"
#include <cassert>
#include <cstdlib>
#include <cstring>


// init meta mem pool
MemPool* create_mem_pool(char* name) {
    MemPool* pool         = (MemPool*)calloc(1, sizeof(MemPool));
    pool->name            = name;
    pool->free_buckets    = std::vector<MemBlock*>(MEM_MAX_BUCKET_NUM, nullptr);
    pool->active_buckets  = std::vector<MemBlock*>(MEM_MAX_BUCKET_NUM, nullptr);
    pool->active_mem_map  = std::unordered_map<void*, size_t>{};
    pool->free_mem_size   = 0;
    pool->active_mem_size = 0;
    pool->all_mem_size    = 0;

    for (int i = 0; i < MEM_INIT_BUCKET_NUM; i++) {
        size_t    block_size = (i + 1) * 8;

        MemBlock* block      = nullptr;
        MemBlock* next       = nullptr;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            block       = (MemBlock*)calloc(1, sizeof(MemBlock)); // 这里不计入分配空间的计算
            block->data = calloc(1, block_size);
            block->next = next;
            next        = block;

            pool->free_mem_size += block_size;
        }

        pool->free_buckets[i] = block;
    }

    pool->all_mem_size = pool->free_mem_size + pool->active_mem_size;

    return pool;
}

void destory_mem_pool(MemPool* pool) {
    assert(pool != nullptr);

#ifdef DEBUG_RVM_MEM_POOL_DETAIL
    dump_mem_pool(pool);
#endif

    // free memory of free buckets
    for (int i = 0; i < MEM_MAX_BUCKET_NUM; i++) {
        MemBlock* next = nullptr;
        for (MemBlock* block = pool->free_buckets[i]; block != nullptr; block = next) {
            next = block->next;

            free(block->data);
            free(block);
        }
    }

    // free memory of active bucket meta info
    for (int i = 0; i < MEM_MAX_BUCKET_NUM; i++) {
        MemBlock* next = nullptr;
        for (MemBlock* block = pool->active_buckets[i]; block != nullptr; block = next) {
            next = block->next;

            free(block);
        }
    }

    // free active data
    for (auto iter = pool->active_mem_map.begin();
         iter != pool->active_mem_map.end();
         iter++) {
        free(iter->first);
    }
}


void dump_mem_pool(MemPool* pool) {
    assert(pool != nullptr);

    unsigned int free_block_num   = 0;
    size_t       free_mem_size    = 0;

    unsigned int active_block_num = 0;
    size_t       active_mem_size  = 0;


    for (int i = 0; i < MEM_MAX_BUCKET_NUM; i++) {
        size_t block_size = (i + 1) * 8;

        for (MemBlock* block = pool->free_buckets[i]; block != nullptr; block = block->next) {
            free_block_num++;
            free_mem_size += block_size;
        }

        for (MemBlock* block = pool->active_buckets[i]; block != nullptr; block = block->next) {
            active_block_num++;
            active_mem_size += block_size;
        }
    }


    printf("+++++++++++ [Memory Pool Summary] ++++++++++++\n");
    printf("Name: %s\n", pool->name);
    printf("\n");
    printf("Free   Block  Num:   %7u\n", free_block_num);
    printf("Active Block  Num:   %7u\n", active_block_num);
    printf("\n");
    printf("Free   Memory Size:  %7ld\n", free_mem_size);
    printf("Active Memory Size:  %7ld\n", active_mem_size);
    printf("\n");
    printf("Active Mem Set Num:  %7ld\n", pool->active_mem_map.size());
    printf("+++++++++++++++++++++++++++++++++++++++++++++\n");

    if (free_mem_size != pool->free_mem_size) {
        ring_error_report("mem pool status is invalid [1]: free_mem_size= %ld, pool->free_mem_size= %ld\n", free_mem_size, pool->free_mem_size);
    }

    if (active_mem_size != pool->active_mem_size) {
        ring_error_report("mem pool status is invalid [2]: active_mem_size= %ld, pool->active_mem_size= %ld\n", active_mem_size, pool->active_mem_size);
    }

    if (pool->free_mem_size + pool->active_mem_size != pool->all_mem_size) {
        ring_error_report("mem pool status is invalid [3]: all_mem_size= %ld, pool->all_mem_size= %ld\n", pool->free_mem_size + pool->active_mem_size, pool->all_mem_size);
    }
}

// alloc memory space fo meta info
void* mem_alloc(MemPool* pool, size_t size) {
    void* res = nullptr;

    if (pool == NULL_MEM_POOL) {
        res = calloc(1, size);
        return res;
    }

    if (size == 0) {
        return nullptr;
    }

    size                   = ROUND_UP8(size);
    int       bucket_index = size / 8 - 1;
    MemBlock* block        = nullptr;

    if (bucket_index > MEM_MAX_BUCKET_NUM) {
        ring_error_report("cant't alloc large sapce, size:%ld\n", size);
    }

    if (pool->free_buckets[bucket_index] == nullptr) {
        size_t    block_size = (bucket_index + 1) * 8;

        MemBlock* block      = nullptr;
        MemBlock* next       = nullptr;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            block       = (MemBlock*)calloc(1, sizeof(MemBlock)); // 这里不计入分配空间的计算
            block->data = calloc(1, block_size);
            block->next = next;
            next        = block;

            pool->free_mem_size += block_size;
            pool->all_mem_size += block_size;
        }
        pool->free_buckets[bucket_index] = block;
    }


    block                              = pool->free_buckets[bucket_index];
    res                                = block->data;
    pool->free_buckets[bucket_index]   = block->next;

    block->next                        = pool->active_buckets[bucket_index];
    pool->active_buckets[bucket_index] = block;

    pool->free_mem_size -= size;
    pool->active_mem_size += size;

    pool->active_mem_map[res] = size;

    memset(res, 0, size);

#ifdef DEBUG_RVM_MEM_POOL_DETAIL
    dump_mem_pool(pool);
#endif
    return res;
}

void* mem_realloc(MemPool* pool, void* ptr, size_t old_size, size_t new_size) {
    if (pool == NULL_MEM_POOL) {
        return realloc(ptr, new_size);
    }
    assert(old_size == ROUND_UP8(old_size));

    void* new_ptr = mem_alloc(pool, new_size);
    memcpy(new_ptr, ptr, old_size);
    mem_free(pool, ptr, old_size);

    return new_ptr;
}

// FIXME: 这里的逻辑不对, 内存泄漏
void mem_free(MemPool* pool, void* ptr, size_t size) {
    if (pool == NULL_MEM_POOL) {
        free(ptr);
        return;
    }
    // assert(size == ROUND_UP8(size));
    if (ptr == nullptr || size == 0) {
        return;
    }

    auto iter = pool->active_mem_map.find(ptr);
    if (iter == pool->active_mem_map.end()) {
        ring_error_report("ptr:%p is not allocated by memory pool", ptr);
    }

    size                   = iter->second;

    int       bucket_index = size / 8 - 1;
    MemBlock* block        = nullptr;

    if (pool->active_buckets[bucket_index] == nullptr) {
        ring_error_report("it is not allocted by memory-pool\n");
    } else {
        block                              = pool->active_buckets[bucket_index];
        pool->active_buckets[bucket_index] = block->next;

        block->data                        = ptr;

        block->next                        = pool->free_buckets[bucket_index];
        pool->free_buckets[bucket_index]   = block;
    }

    pool->free_mem_size += size;
    pool->active_mem_size -= size;

    pool->active_mem_map.erase(ptr);
}

void test_mem_pool() {
    MemPool* pool = create_mem_pool((char*)"test");
    dump_mem_pool(pool);
    std::vector<void*>              tmp(MEM_BLOCK_NUM, nullptr);
    std::vector<std::vector<void*>> res(MEM_MAX_BUCKET_NUM, tmp);
    size_t                          sum = 0;

    for (int i = 0; i < MEM_MAX_BUCKET_NUM; i++) {
        size_t block_size = (i + 1) * 8;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            void* ptr = mem_alloc(pool, block_size);
            res[i][j] = ptr;
            sum += block_size;
        }
    }
    printf("----------------sum:%ld\n", sum);
    dump_mem_pool(pool);

    for (int i = 0; i < MEM_MAX_BUCKET_NUM; i++) {
        size_t block_size = (i + 1) * 8;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            mem_free(pool, res[i][j], block_size);
        }
    }
    dump_mem_pool(pool);
}