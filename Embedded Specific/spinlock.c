/******************************************************************************
Spinlock
*******************************************************************************/
#include <stdatomic.h>

 // 1 = free, 0 = held
static atomic_uint sig;

void init() {
    atomic_store(&sig,1);
}

void lock() {
    unsigned int FREE = 1;
    while(1) {
        if(atomic_compare_exchange_weak(&sig, &FREE, 0)) return;
    }
}

void unlock() {
    atomic_store(&sig,1);
}

unsigned int readlock() {
    return atomic_load(&sig);
}
