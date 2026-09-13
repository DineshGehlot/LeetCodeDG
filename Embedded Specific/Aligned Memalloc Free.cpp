/******************************************************************************
Question: Write a memory allocation function (and corresponding free function)
that returns a block of memory aligned to the specified alignment value. You
may assume that the alignment is a power of 2 (1, 2, 4, 8, 16, ...).
*******************************************************************************/

#include <iostream>
#include <cstdint>

using namespace std;

//void* myMalloc(int size, int PowerBitAlign) {
void* myMalloc(size_t size, size_t alignment) {
    // Allocote (Extra) = size + alignment + size of address  (actual alignenment)
    // start from current allocated +4 byte
    // return next aligned

    size_t overhead = alignment -1 + sizeof(uintptr_t);
    uint8_t *allocatedAddr = (uint8_t*)malloc(size + overhead);
    void* aligned = (void*)((uintptr_t)(allocatedAddr + overhead) & ~(alignment - 1));
    
    uintptr_t* temp = (uintptr_t*)(aligned - sizeof(uintptr_t));
    *temp = (uintptr_t)allocatedAddr;
    
    return (void*)aligned;
}

void myFree(void* addr) {

    uintptr_t *temp = (uintptr_t*)((uint8_t*)addr - sizeof(uintptr_t));
    free((void*)*temp);
}

int main()
{
    void * addr1, * addr2, * addr3, *addr4;
    addr1 = myMalloc(560, 16);
    cout << "16 byte aligned address allocated: " << hex << addr1 <<endl;
    myFree(addr1);
    
    addr2 = myMalloc(560, 32);
    cout << "32 byte aligned address allocated: " << hex << addr2 <<endl;
    myFree(addr2);
    
    addr3 = myMalloc(560, 64);
    cout << "64 byte aligned address allocated: " << hex << addr3 <<endl;
    myFree(addr3);
    
    addr4 = myMalloc(506, 128);
    cout << "128 byte aligned address allocated: " << hex << addr4 <<endl;
    myFree(addr4);
    
    addr1 = myMalloc(506, 256);
    cout << "256 byte aligned address allocated: " << hex << addr1 <<endl;

    
    addr2 = myMalloc(506, 512);
    cout << "512 byte aligned address allocated: " << hex << addr2 <<endl;

    addr3 = myMalloc(563, 1024);
    cout << "1024 byte aligned address allocated: " << hex << addr3 <<endl;

    addr4 = myMalloc(568, 2048);
    cout << "2048 byte aligned address allocated: " << hex << addr4 <<endl;

    myFree(addr4);
    myFree(addr3);
    myFree(addr2);
    myFree(addr1);
    
    return 0;
}