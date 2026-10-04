/******************************************************************************
UART Driver

Imagine the following UART hardware:
    UART_BASE + 0x00  DATA
    UART_BASE + 0x04  STATUS
    UART_BASE + 0x08  CONTROL
    UART_BASE + 0x0C  BAUD

STATUS:
    bit 0: RX_READY     1 = received byte available
    bit 1: TX_EMPTY     1 = transmitter can accept a byte
    bit 2: RX_ERROR     1 = receive error

CONTROL:
    bit 0: RX_ENABLE
    bit 1: TX_ENABLE

Implement:
    bool uart_init(uintptr_t base, uint32_t baud);
    bool uart_putc(char c);
    bool uart_getc(char* c);
    
Requirements:
1. uart_init() should:
    initialize the UART
    configure baud rate
    enable RX and TX

2. uart_putc() should:
    wait until TX_EMPTY
    write the character to DATA
    return success/failure

3. uart_getc() should:
    check RX_READY
    read the received character
    detect RX_ERROR
    return success/failure

4. Do not busy-wait forever.
*******************************************************************************/

#include <cstdint>
enum uartReg {
    DATA    = 0x00,
    STATUS  = 0x04,
    CONTROL = 0x08,
    BAUD    = 0x0C
};

constexpr uint32_t RX_ENABLE = 1U <<0;
constexpr uint32_t TX_ENABLE = 1U <<1;

constexpr uint32_t RX_READY = 1U <<0; 
constexpr uint32_t TX_EMPTY = 1U <<1;
constexpr uint32_t RX_ERROR = 1U <<2;

constexpr uint32_t UART_TIMEOUT = 0xFF;

volatile uintptr_t uartBase = 0;
volatile uint32_t  *uartStatus, *uartControl, *uartBaud;
volatile char  *uartData;

bool isUartInit = false;

bool uart_init(uintptr_t base, uint32_t baud) {
    
    if (base == 0 || baud == 0) return false;
    
    uartBase = base;
    
    uartData = reinterpret_cast<volatile char*>(uartBase + DATA);
    uartStatus = reinterpret_cast<volatile uint32_t*>(uartBase + STATUS);
    uartControl = reinterpret_cast<volatile uint32_t*>(uartBase + CONTROL);
    uartBaud = reinterpret_cast<volatile uint32_t*>(uartBase + BAUD);
    
    //configure baud rate 
    *uartBaud = baud;
    
    //enable RX and TX
    *uartControl |= (RX_ENABLE | TX_ENABLE);
    
    isUartInit = true;
    return true;
}

bool uart_putc(char c) {
    if(!isUartInit) return false;
    for (int i = 0; i < UART_TIMEOUT ; ++i) {

        if(*uartStatus & TX_EMPTY) {
            *uartData = c;
            return true;
        }
    }
    return false; //transmitter not ready
}

bool uart_getc(char* c) {
    if(!isUartInit) return false;
    if (c == nullptr) return false;
    for (int i = 0; i < UART_TIMEOUT ; ++i) {
        if(*uartStatus & RX_READY) {
            if(*uartStatus & RX_ERROR) {
                return false; // read error
            }
        *c = reinterpret_cast<char>(*uartData);
        return true;
        }    
    }

    return false; //Receiver not ready
}

int main()
{
    uintptr_t base = reinterpret_cast<uintptr_t>(new uint8_t[16]);
    uart_init(base, 0XFACEFACE);
    uart_putc('a');
    char ch; 
    uart_getc(&ch);
    
    delete[] reinterpret_cast<uint8_t*>(base);
    
    return 0;
}