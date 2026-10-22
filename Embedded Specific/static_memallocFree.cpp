/*
Problem statement
Implement a fixed-size memory pool that manages a statically allocated memory region. The pool contains 16 blocks, each 64 bytes.

Implement these APIs:
```
#define POOL_BLOCK_SIZE 64
#define POOL_BLOCK_COUNT 16

void mempool_init(void);
void *mempool_alloc(void);
bool mempool_free(void *ptr);
```
Requirements
1. No dynamic memory allocation (malloc, calloc, or free).
2. mempool_alloc() returns a pointer to an available block, or NULL if the pool is exhausted.
3. mempool_free() releases a previously allocated block.
4. Reject invalid pointers, including pointers outside the pool and pointers that don't point to the beginning of a block.
5. Detect double frees and return false.
6. Returned blocks must satisfy the alignment requirements of the supported objects.
7. Assume allocation and freeing may be called from multiple tasks. Explain how you would make the implementation thread-safe on an embedded target.
*/

#include <cstdint>
#include <mutex>

#define POOL_BLOCK_SIZE 64
#define POOL_BLOCK_COUNT 16
#define FULL_MASK ((1U<<POOL_BLOCK_COUNT)-1)


typedef struct {
    uint16_t freemap;
    uint8_t buff[POOL_BLOCK_SIZE*POOL_BLOCK_COUNT];
    std::mutex m;
}buffer_t;

buffer_t pPool;
buffer_t *pool = &pPool;


void mempool_init(void) {
    pool->freemap = 0;
}

void *mempool_alloc(void){
     pool->m.lock();
    void* allocated = nullptr;
    if(pool->freemap!=FULL_MASK) {
        for(int i = 0; (i<POOL_BLOCK_COUNT) && !allocated; ++i) {
            if((pool->freemap & (1U<<i))==0) {
                uint8_t *nextP = pool->buff + (i *POOL_BLOCK_SIZE);
                allocated = reinterpret_cast<void*>(nextP);
                pool->freemap |= (1U<<i);
            }
        }
    }
     pool->m.unlock();
    return allocated;
}

bool mempool_free(void *ptr) {
    
    if(!ptr) return false; // null pointer free operation
    
    pool->m.lock();
    uintptr_t curr = reinterpret_cast<uintptr_t>(ptr);
    uintptr_t base = reinterpret_cast<uintptr_t>(pool->buff);
    
    if (curr<base || curr >=  (base + sizeof( pool->buff))) {
         pool->m.unlock();
          return false; // out of range
    }
        
    if((curr%POOL_BLOCK_SIZE) != (base%POOL_BLOCK_SIZE)) {
        pool->m.unlock();
        return false; // unaligned address
    }
        
    
    uint32_t index = ((curr-base)/POOL_BLOCK_SIZE);
    
    uint16_t MASK = 1U<<index;
    if ((pool->freemap & MASK)==0) {
         pool->m.unlock();
         return false; // double free
    }
        
    pool->freemap &= (~MASK);
    
    pool->m.unlock();
    return true;
}
