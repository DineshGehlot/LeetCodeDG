/******************************************************************************
Left shift n bits
*******************************************************************************/

#include <iostream>
#include <cstdint>

using namespace std;
uint32_t  leftShift(uint32_t num, uint32_t n) {
    n = n%32;
    return (num << n) | (num >> (32 -n));
}

int main()
{
    cout<< hex <<leftShift(0xDEADBEEF, 24) << endl;
    cout<< hex <<leftShift(0xFACEBACE, 32) << endl;
    return 0;
}