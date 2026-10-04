/******************************************************************************

Write a Memory-Mapped GPIO Driver

The processor communicates with a GPIO peripheral through memory-mapped
I/O registers.

Your task is to implement a small GPIO driverthat can initialize a pin,
configure it as an output, and set or clear its value.

1. The hardware provides the following registers.

| Register   | Offset | Description                                  |
| ---------- | -----: | -------------------------------------------- |
| `GPIO_DIR` | `0x00` | Direction register: 1 = output, 0 = input    |
| `GPIO_OUT` | `0x04` | Output register: 1 = high, 0 = low           |
| `GPIO_IN`  | `0x08` | Input register: reads the current pin values |

2. Assume the GPIO peripheral's base address is 0x40000000.

3. Each register is 32 bits wide, and the peripheral supports 32 GPIO pins.
For example:
    * Pin 0 corresponds to bit 0.
    * Pin 5 corresponds to bit 5.
    * Pin 31 corresponds to bit 31.

4. Implement the following functions in C or C++:

    1. bool gpio_init(uintptr_t base_addr);
        gpio_init() should initialize the driver with the supplied peripheral base address.
    2. bool gpio_set_direction(uint8_t pin, bool output);
        gpio_set_direction() should configure the selected pin as an output or input.
    3. bool gpio_write(uint8_t pin, bool value);
        gpio_write() should set or clear the selected pin's output value.
    4. bool gpio_read(uint8_t pin, bool* value);
        gpio_read() should read the selected pin's current value from the input register.

5. Error handling
    1. Reject invalid pin numbers.
    2. Reject operations when the driver has not been initialized.
    3. Reject a null pointer passed to gpio_read().
    4. Return an appropriate success or failure result.

6. Use appropriate memory-mapped I/O access. Do not treat these registers asordinary RAM.
For this exercise, assume:
    * The peripheral is mapped into the processor's address space.
    * The register offsets and bit definitions are correct.
    * The hardware is powered and accessible.
    * The platform provides the necessary mapping and access permissions.

*******************************************************************************/

#include <iostream>
#include <cstdint>

using namespace std;

class memoryMappedGPIO {
    private:
    enum REG {
        GPIO_DIR    = 0x00,
        GPIO_OUT    = 0x04,
        GPIO_IN     = 0x08,
    };
    
    uintptr_t regBase;
    volatile uint32_t *regDir, *regOut, *regIn;
    
    bool gpio_init(uintptr_t base_addr) {
        regBase = base_addr;
        regDir = reinterpret_cast<volatile uint32_t*>(regBase + GPIO_DIR);
        regOut = reinterpret_cast<volatile uint32_t*>(regBase + GPIO_OUT);
        regIn = reinterpret_cast<volatile uint32_t*>(regBase + GPIO_IN);
        return true;
    }
    
    bool isOutDir(uint8_t pin) {
        return *regDir & (1<<pin);
    }
    
    bool isValidPin(uint8_t pin){
        if(pin > 31) {
            cout << "Invalid Pin" <<endl;
            return false;
        }
        return true;
    }
    
    public:

    memoryMappedGPIO(uintptr_t base_addr) {
        gpio_init(base_addr);
    }

    bool gpio_set_direction(uint8_t pin, bool output) {
        if(!isValidPin(pin)) return false;
        
        uint32_t MASK = ~(1 << pin);
        *regDir = (*regDir & MASK) | (output << pin);
        
        return true;
    }

    bool gpio_write(uint8_t pin, bool value) {
        if(!isValidPin(pin)) return false;
        
        uint32_t MASK = ~(1 << pin);
        if (isOutDir(pin))
            *regOut = (*regOut & MASK) | (value << pin);
        else
            *regIn = (*regIn & MASK) | (value << pin);
        
        return true;
    }

    bool gpio_read(uint8_t pin, bool* value) {
        if(!isValidPin(pin)) return false;
        if(value == nullptr) {
            cout << "Null Pointer" <<endl;
            return false;
        }
        if (isOutDir(pin))
            *value = *regOut & (1 << pin);
        else
            *value = *regIn & (1 << pin);
        
        return true;
    }
};

int main() {
    uintptr_t base = reinterpret_cast<uintptr_t>(new uint8_t[12]);
    bool output;
    memoryMappedGPIO *sensorGPIO = new memoryMappedGPIO(base);
    sensorGPIO->gpio_set_direction(1,1);
    sensorGPIO->gpio_write(1,0);
    sensorGPIO->gpio_read(1,&output);
    
    sensorGPIO->gpio_set_direction(1,0);
    sensorGPIO->gpio_write(1,0);
    sensorGPIO->gpio_read(1,&output);
    
    sensorGPIO->gpio_set_direction(32,1);
    sensorGPIO->gpio_read(1,nullptr);
    
    return 0;
}

