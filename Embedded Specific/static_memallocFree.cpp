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