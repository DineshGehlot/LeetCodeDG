/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

// Implement memcpy() optimized for 64-bit alignment

#include <iostream>
#include <cstdint>
using namespace std;

void myMemCpy(void *dest, const void* src, int size) {
 
    const uint8_t *src8 = (const uint8_t*)(src);
    uint8_t *dest8 =  (uint8_t*)(dest);
    

    if(((((uint64_t)dest8 ^ (uint64_t)src8)) & 7)==0) {

        while (size && ((uint64_t)dest8 & 7)) {
            *dest8++ = *src8++;
            size--;
        }
        
        const uint64_t* src64 = (const uint64_t*)(src8);
        uint64_t *dest64 = (uint64_t*)(dest8);
        
        while(size >= 8) {
            *dest64++ = *src64++;
            size -= 8;
        }
        src8 = (const uint8_t*)(src64);
        dest8 =  (uint8_t*)(dest64);
    }
    
    while (size)
    {
        *dest8++ = *src8++;
        size--;  
    }
}


int main()
{
    constexpr int n = 34;

    uint8_t *src =static_cast<uint8_t *>(malloc(n));

    uint8_t *dst = static_cast<uint8_t *>(malloc(n));

    if (!src || !dst) return 1;

    for (int i = 0; i < n; i++)
    {
        src[i] = 0x0D;
        dst[i] = 0x0F;
    }

    cout << "Before memcpy: ";

    for (int i = 0; i < n; i++)
        cout << hex << static_cast<int>(dst[i]);

    cout << endl;

    myMemCpy(dst, src, n);

    cout << "After memcpy:  ";

    for (int i = 0; i < n; i++)
        cout << hex << static_cast<int>(dst[i]);

    cout << endl;

    free(src);
    free(dst);

    return 0;
}

// Next memmove, what if they overlap