/******************************************************************************

Embedded-specific bit manipulation

You have this 32-bit hardware status register:

#define STATUS_REG (*(volatile uint32_t *)0x40001000U)

Its fields are:
31          16 15      8 7       4 3       0
+-------------+---------+---------+---------+
|    RESERVED |  ERROR  |  MODE   |  STATE  |
+-------------+---------+---------+---------+

    STATE : bits 0-3
    MODE  : bits 4-7
    ERROR : bits 8-15

Write code to:
1. Extract STATE
2. Extract MODE
3. Extract ERROR
4. Set MODE = 5 without changing STATE or ERROR
5. Explain how you would avoid accidentally modifying the reserved bits

*******************************************************************************/

#define STATUS_REG (*(volatile uint32_t *)0x40001000U)

#define STATE_MASK 0x0000000FU
#define STATE_MODE 0x000000F0U
#define STATE_ERROR 0x0000FF00U


#define STATE_SHIFT 0
#define MODE_SHIFT 4
#define MASK_SHIFT 8

#define extractState() ((STATUS_REG & STATE_MASK) >> STATE_SHIFT)
#define extractMode() ((STATUS_REG & STATE_MODE) >> MODE_SHIFT)
#define extractMask() ((STATUS_REG & STATE_ERROR) >> MASK_SHIFT)

void setMode(uint32_t n) {
    n = n << MODE_SHIFT;
    if (n & ~STATE_MODE) return;
    
    STATUS_REG = ((STATUS_REG & ~STATE_MODE) | n);
}


