#include "ring.h"


static MemPool* mem_pool = nullptr;


// init meta mem pool
void init_mem_pool() {
    assert(mem_pool == nullptr);

    mem_pool                  = (MemPool*)malloc(sizeof(MemPool));
    mem_pool->free_buckets    = std::vector<MemBlock*>(MEM_BUCKET_NUM, nullptr);
    mem_pool->active_buckets  = std::vector<MemBlock*>(MEM_BUCKET_NUM, nullptr);
    mem_pool->free_mem_size   = 0;
    mem_pool->active_mem_size = 0;

    for (int i = 0; i < MEM_BUCKET_NUM; i++) {
        size_t    block_size = (i + 1) * 8;

        MemBlock* block      = nullptr;
        MemBlock* next       = nullptr;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            block       = (MemBlock*)malloc(sizeof(MemBlock)); // 这里不计入分配空间的计算
            block->data = malloc(block_size);
            block->next = next;
            next        = block;

            mem_pool->free_mem_size += block_size;
        }

        mem_pool->free_buckets[i] = block;
    }
}

void dump_mem_pool() {
    assert(mem_pool != nullptr);

    printf("-------------- free buckets --------------\n");
    for (int i = 0; i < MEM_BUCKET_NUM; i++) {
        size_t    block_size = (i + 1) * 8;

        int       block_num  = 0;
        MemBlock* block      = mem_pool->free_buckets[i];
        while (block != nullptr) {
            block_num++;
            block = block->next;
        }

        printf("i:%4d, block_size:%08ld block_num:%04d\n", i, block_size, block_num);
    }
    printf("-------------- free buckets --------------\n");

    printf("++++++++++++++ allocated buckets ++++++++++++++\n");
    for (int i = 0; i < MEM_BUCKET_NUM; i++) {
        size_t    block_size = (i + 1) * 8;

        int       block_num  = 0;
        MemBlock* block      = mem_pool->active_buckets[i];
        while (block != nullptr) {
            block_num++;
            block = block->next;
        }

        printf("i:%4d, block_size:%08ld block_num:%04d\n", i, block_size, block_num);
    }
    printf("++++++++++++++ allocated buckets ++++++++++++++\n");

    printf("free_mem_size:%ld, active_mem_size:%ld\n", mem_pool->free_mem_size, mem_pool->active_mem_size);
}

// malloc memory space fo meta info
void* meta_malloc(size_t size) {
    assert(mem_pool != nullptr);
    if (size == 0) {
        return nullptr;
    }

    size_t    alloc_size   = ROUND_UP8(size);
    int       bucket_index = alloc_size / 8 - 1;
    MemBlock* block        = nullptr;

    if (mem_pool->free_buckets[bucket_index] == nullptr) {
        // TODO: 分配内存, 直接添加到 active_buckets
        size_t    block_size = (bucket_index + 1) * 8;

        MemBlock* block      = nullptr;
        MemBlock* next       = nullptr;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            block       = (MemBlock*)malloc(sizeof(MemBlock)); // 这里不计入分配空间的计算
            block->data = malloc(block_size);
            block->next = next;
            next        = block;

            mem_pool->free_mem_size += block_size;
        }
        mem_pool->free_buckets[bucket_index] = block;
    }

    block                                  = mem_pool->free_buckets[bucket_index];
    mem_pool->free_buckets[bucket_index]   = block->next;

    block->next                            = mem_pool->active_buckets[bucket_index];
    mem_pool->active_buckets[bucket_index] = block;

    mem_pool->free_mem_size -= alloc_size;
    mem_pool->active_mem_size += alloc_size;

    return block->data;
}

void meta_free(void* ptr, size_t size) {
    assert(mem_pool != nullptr);
    assert(size == ROUND_UP8(size));
    if (ptr == nullptr || size == 0) {
        return;
    }

    int       bucket_index = size / 8 - 1;
    MemBlock* block        = nullptr;

    if (mem_pool->active_buckets[bucket_index] == nullptr) {
        printf("it is not allocted by memory-pool\n");
        exit(1);
    } else {
        block                                  = mem_pool->active_buckets[bucket_index];
        mem_pool->active_buckets[bucket_index] = block->next;

        block->data                            = ptr;
        block->next                            = mem_pool->free_buckets[bucket_index];
        mem_pool->free_buckets[bucket_index]   = block;
    }

    mem_pool->free_mem_size += size;
    mem_pool->active_mem_size -= size;
}

void test_mem_pool() {
    init_mem_pool();
    dump_mem_pool();
    std::vector<void*>              tmp(MEM_BLOCK_NUM, nullptr);
    std::vector<std::vector<void*>> res(MEM_BUCKET_NUM, tmp);
    size_t                          sum = 0;

    for (int i = 0; i < MEM_BUCKET_NUM; i++) {
        size_t block_size = (i + 1) * 8;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            void* ptr = meta_malloc(block_size);
            res[i][j] = ptr;
            sum += block_size;
        }
    }
    printf("----------------sum:%ld\n", sum);
    dump_mem_pool();

    for (int i = 0; i < MEM_BUCKET_NUM; i++) {
        size_t block_size = (i + 1) * 8;
        for (int j = 0; j < MEM_BLOCK_NUM; j++) {
            meta_free(res[i][j], block_size);
        }
    }
    dump_mem_pool();
}