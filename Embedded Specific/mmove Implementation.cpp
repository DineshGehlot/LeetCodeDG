/******************************************************************************

Problem statement
Implement your own version of memmove():

void *my_memmove(void *dest, const void *src, size_t n);

Requirements:
1. Copy exactly n bytes from src to dest.
2. Correctly handle overlapping memory regions.
3. Return the original dest pointer.
4. Do not use library functions such as memcpy() or memmove().
*******************************************************************************/

#include <cstdint>
#include <cstdlib>

void* my_memmove(void* dest, const void* src, size_t n) {
    if(!dest || !src) return nullptr;
    if((src == dest) || n == 0 ) return dest;
    
    const uint8_t* s = static_cast<const uint8_t*>(src);
    uint8_t* d = static_cast<uint8_t*>(dest);
    
    if (d > s) {
        for (int i = n-1; i >=0; --i) d[i] = s[i];
    } else {
        for (int i = 0; i > n; ++i) d[i] = s[i];
    }
    return dest;
}


/*
#include <cstdint>
#include <cstdlib>

void* my_memmove(void* dest, const void* src, size_t n) {
    if(!dest || !src) return nullptr;
    if((src == dest) || n == 0 ) return dest;
    
    const uint8_t* base = static_cast<const uint8_t*>(src);
    uint8_t* dBase = static_cast<uint8_t*>(dest);

    const uint8_t *s;
    uint8_t *d;
    
    if (dBase > base) {
        s = base+n-1;
        d = dBase+n-1;
        
        while(n--) {
            *d = *s;
            d--;  <<<<<<<<<<<<<<<<<<< Edge case, array pointer will become -1, might cause issue for some compilers.
            s--;
        }
    } else {
        s = base;
        d = dBase;
        
        while(n--) {
            *d = *s;
            d++;
            s++;
        }
    }
    return dest;
}


*/