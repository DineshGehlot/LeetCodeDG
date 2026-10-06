/******************************************************************************

Set/Clear/Test a bit

You have a 32-bit hardware register:

    volatile uint32_t REG = 0x00000000;

Write C code/macros to implement:
* SET_BIT(REG, n)
* CLEAR_BIT(REG, n)
* TOGGLE_BIT(REG, n)
* TEST_BIT(REG, n)

Requirements:
1. n can be 0–31.
2. SET_BIT must set only bit n.
3. CLEAR_BIT must clear only bit n.
4. TOGGLE_BIT must invert only bit n.
5. TEST_BIT should return 0 or 1.
6. Don't use loops.

*******************************************************************************/

#include <cstdint>

#define SET_BIT(r, n) r|(1U<<n)
#define CLEAR_BIT(r, n) r&(~(1U<<n))
#define TOGGLE_BIT(r, n) r^(1U<<n)
#define TEST_BIT(r, n) r&(1U<<n)

volatile uint32_t REG = 0x00000000;


int main()
{
    REG = SET_BIT(REG,0); 
    REG = CLEAR_BIT(REG,0); 
    REG = SET_BIT(REG,0); 
    REG = TOGGLE_BIT(REG,0); 
    TEST_BIT(REG,0); 
    REG = SET_BIT(REG,0);
    TEST_BIT(REG,0);
    return 0;
}