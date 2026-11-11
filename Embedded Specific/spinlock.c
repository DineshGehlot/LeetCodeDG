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
    unsigned int FREE;
    while(1) {
        FREE = 1;
        if(atomic_compare_exchange_weak(&sig, &FREE, 0)) return;
    }
}

void unlock() {
    atomic_store(&sig,1);
}

unsigned int readlock() {
    return atomic_load(&sig);
}

/***************************************************************************
lock:
LDAXR W1, [X0] 		// Acquire exclusive write and load memory pointed by x0 to w1
CBZ W1, lock  		// compare if w1 is zero, if yes means held, loopback
STXR W2, WZR, [X0]	// store exclusive 0=Acquire to the memory address held in x0, store status in W2
CBNZ W2, lock 		// if W2 is non zero, store failed loopback

unlock:
MOV W1, #1  		// store w1 with value 1 = free
STLR W1, [X0]  		//stores the value in w1 to the memory address held in x0, with release semantics.
***************************************************************************/

