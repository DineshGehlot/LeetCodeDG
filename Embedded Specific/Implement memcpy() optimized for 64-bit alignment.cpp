// Implementation v2.0

// Optimize memcpy() implementation for 64-bit alignment

#include<cstdint>
#include<iostream>
#include<cstdlib>

using namespace std;

void memcpy64(uint8_t* dest, const uint8_t* src, size_t n) {

    constexpr int ALIGN = 7;
    uint8_t* dest8 = reinterpret_cast<uint8_t*>(dest);
    const uint8_t* src8 = reinterpret_cast<const uint8_t*>(src);

   //if(((reinterpret_cast<uintptr_t>((dest8) ^ reinterpret_cast<uintptr_t>((src8)) & MASK)==0) {
    if((reinterpret_cast<uintptr_t>(dest8) & ALIGN) == (reinterpret_cast<uintptr_t>(src8) & ALIGN)){
       while(n && (reinterpret_cast<uintptr_t>(src8) & ALIGN)) {
           *dest8++ = *src8++;
           --n;
       }
       uint64_t* dest64 = reinterpret_cast<uint64_t *>(dest8);
       const uint64_t* src64 = reinterpret_cast<const uint64_t *>(src8);
       
        while(n > ALIGN) {
           *dest64++ = *src64++;
           n -=8;
       }
        dest8 = reinterpret_cast<uint8_t*>(dest64);
        src8 = reinterpret_cast<const uint8_t*>(src64);
    }
    while(n) {
           *dest8++ = *src8++;
           --n;
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

    memcpy64(dst, src, n);

    cout << "After memcpy:  ";

    for (int i = 0; i < n; i++)
        cout << hex << static_cast<int>(dst[i]);

    cout << endl;

    free(src);
    free(dst);

    return 0;
}