#include "ring.h"

// init meta mem pool
MemPool* create_mem_pool(char* name) {
    MemPool* pool         = (MemPool*)malloc(sizeof(MemPool));
    pool->name            = name;
    pool->free_buckets    = std::vector<MemBlock*>(MEM_BUCKET_NUM, nullptr);
    pool->active_buckets  = std::vector<MemBlock*>(MEM_BUCKET_NUM, nullptr);
    pool->free_mem_size   = 0;
    pool->active_mem_size = 0;
    pool->all_mem_size    = 0;

    for (int i = 0; i < MEM_BUCKET_NUM; i++) {
        size_t    block_size = (i + 1) * 8;

        MemBlock* block      = nullptr;
        MemBlock* next       = nullptr;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            block       = (MemBlock*)malloc(sizeof(MemBlock)); // 这里不计入分配空间的计算
            block->data = malloc(block_size);
            block->next = next;
            next        = block;

            pool->free_mem_size += block_size;
        }

        pool->free_buckets[i] = block;
    }

    pool->all_mem_size = pool->free_mem_size;

    return pool;
}

void destory_mem_pool(MemPool* pool) {
    assert(pool != nullptr);

#ifdef DEBUG_RVM_MEM_POOL_DETAIL
    dump_mem_pool(pool);
#endif

    // free memory of free buckets
    for (int i = 0; i < MEM_BUCKET_NUM; i++) {
        MemBlock* next = nullptr;
        for (MemBlock* block = pool->free_buckets[i]; block != nullptr; block = next) {
            next = block->next;

            free(block->data);
            free(block);
        }
    }

    // free memory of active buckets
    for (int i = 0; i < MEM_BUCKET_NUM; i++) {
        MemBlock* next = nullptr;
        for (MemBlock* block = pool->active_buckets[i]; block != nullptr; block = next) {
            next = block->next;

            // free(block->data);
            free(block);
        }
    }
}


void dump_mem_pool(MemPool* pool) {
    assert(pool != nullptr);

    unsigned int free_block_num   = 0;
    size_t       free_mem_size    = 0;

    unsigned int active_block_num = 0;
    size_t       active_mem_size  = 0;


    for (int i = 0; i < MEM_BUCKET_NUM; i++) {
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

    assert(free_mem_size == pool->free_mem_size);
    assert(active_mem_size == pool->active_mem_size);

    assert(pool->free_mem_size + pool->active_mem_size == pool->all_mem_size);


    printf("+++++++++++ [Memory Pool Summary] ++++++++++++\n");
    printf("Name: %s\n", pool->name);
    printf("\n");
    printf("Free   Block  Num:   %7u\n", free_block_num);
    printf("Active Block  Num:   %7u\n", active_block_num);
    printf("\n");
    printf("Free   Memory Size:  %7ld\n", free_mem_size);
    printf("Active Memory Size:  %7ld\n", active_mem_size);
    printf("+++++++++++++++++++++++++++++++++++++++++++++\n");
}

// malloc memory space fo meta info
void* mem_alloc(MemPool* pool, size_t size) {
    assert(pool != nullptr);
    if (size == 0) {
        return nullptr;
    }

    size_t    alloc_size   = ROUND_UP8(size);
    int       bucket_index = alloc_size / 8 - 1;
    MemBlock* block        = nullptr;

    if (pool->free_buckets[bucket_index] == nullptr) {
        // TODO: 分配内存, 直接添加到 active_buckets
        size_t    block_size = (bucket_index + 1) * 8;

        MemBlock* block      = nullptr;
        MemBlock* next       = nullptr;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            block       = (MemBlock*)malloc(sizeof(MemBlock)); // 这里不计入分配空间的计算
            block->data = malloc(block_size);
            block->next = next;
            next        = block;

            pool->free_mem_size += block_size;
        }
        pool->free_buckets[bucket_index] = block;
    }

    void* res                          = nullptr;

    block                              = pool->free_buckets[bucket_index];
    res                                = block->data;
    block->data                        = nullptr;
    pool->free_buckets[bucket_index]   = block->next;

    block->next                        = pool->active_buckets[bucket_index];
    pool->active_buckets[bucket_index] = block;

    pool->free_mem_size -= alloc_size;
    pool->active_mem_size += alloc_size;

    return res;
}

void* mem_realloc(MemPool* pool, void* ptr, size_t old_size, size_t new_size) {
    assert(pool != nullptr);
    assert(old_size == ROUND_UP8(old_size));

    void* new_ptr = mem_alloc(pool, new_size);
    memcpy(new_ptr, ptr, old_size);
    mem_free(pool, ptr, old_size);

    return new_ptr;
}

void mem_free(MemPool* pool, void* ptr, size_t size) {
    assert(pool != nullptr);
    // assert(size == ROUND_UP8(size));
    if (ptr == nullptr || size == 0) {
        return;
    }

    int       bucket_index = size / 8 - 1;
    MemBlock* block        = nullptr;

    if (pool->active_buckets[bucket_index] == nullptr) {
        printf("it is not allocted by memory-pool\n");
        exit(1);
    } else {
        block                              = pool->active_buckets[bucket_index];
        pool->active_buckets[bucket_index] = block->next;

        block->data                        = ptr;

        block->next                        = pool->free_buckets[bucket_index];
        pool->free_buckets[bucket_index]   = block;
    }

    pool->free_mem_size += size;
    pool->active_mem_size -= size;
}

void test_mem_pool() {
    MemPool* pool = create_mem_pool((char*)"test");
    dump_mem_pool(pool);
    std::vector<void*>              tmp(MEM_BLOCK_NUM, nullptr);
    std::vector<std::vector<void*>> res(MEM_BUCKET_NUM, tmp);
    size_t                          sum = 0;

    for (int i = 0; i < MEM_BUCKET_NUM; i++) {
        size_t block_size = (i + 1) * 8;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            void* ptr = mem_alloc(pool, block_size);
            res[i][j] = ptr;
            sum += block_size;
        }
    }
    printf("----------------sum:%ld\n", sum);
    dump_mem_pool(pool);

    for (int i = 0; i < MEM_BUCKET_NUM; i++) {
        size_t block_size = (i + 1) * 8;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            mem_free(pool, res[i][j], block_size);
        }
    }
    dump_mem_pool(pool);
}