/******************************************************************************
Question: Write a memory allocation function (and corresponding free function)
that returns a block of memory aligned to the specified alignment value. You
may assume that the alignment is a power of 2 (1, 2, 4, 8, 16, ...).
*******************************************************************************/

#include <iostream>
#include <cstdint>
#include <cstdlib>

using namespace std;

//void* myMalloc(int size, int PowerBitAlign) {
void* myMalloc(size_t size, size_t alignment) {
    // Allocote (Extra) = size + alignment + 4 byte (actual alignenment)
    // start from current allocated +4 byte
    // return next aligned

    int n = size + alignment -1 + sizeof(uintptr_t);
    int MASK = alignment -1; 
    void *allocatedAddr = (void*)malloc(n);
    uint8_t* temp = (uint8_t*) allocatedAddr + sizeof(uintptr_t);
    do {
        temp++;
    }
    while((uintptr_t)temp & (MASK));
    
    uintptr_t* temp2 = (uintptr_t*)(temp - sizeof(uintptr_t));
    *temp2 = (uintptr_t)allocatedAddr;
    
    return (void*)temp;
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