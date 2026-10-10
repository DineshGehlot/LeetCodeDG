/******************************************************************************

Write a Memory-Mapped GPIO Driver

The processor communicates with a GPIO peripheral through memory-mapped
I/O registers.

Your task is to implement a small GPIO driver that can initialize a pin,
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

class memoryMappedGPIO {
private:
    enum REG {
    GPIO_DIR = 0x00,
    GPIO_OUT = 0x04,
    GPIO_IN  = 0x08
    };

    volatile uint32_t* reg_dir = nullptr;
    volatile uint32_t* reg_in = nullptr;
    volatile uint32_t* reg_out = nullptr;
    
    static constexpr uint8_t MAX_PIN = 32;
    
    bool initialized = false;

public:
    bool gpio_init(uintptr_t base_addr) {
        if(0 == base_addr) return initialized = false;
        reg_dir = reinterpret_cast<volatile uint32_t*>(base_addr);
        reg_out = reinterpret_cast<volatile uint32_t*>(base_addr + GPIO_OUT);
        reg_in  = reinterpret_cast<volatile uint32_t*>(base_addr + GPIO_IN);
        
        return initialized = true;
    }
    
    bool gpio_set_direction(uint8_t pin, bool output) {
        if(pin>=MAX_PIN || !initialized) return false;
        const uint32_t MASK = 1U << pin;
        if (output)
            *reg_dir |= MASK;
        else
            *reg_dir &= ~MASK;
        return true;
    }
    
    bool gpio_write(uint8_t pin, bool value) {
        if(pin>=MAX_PIN || !initialized) return false;
        
        const uint32_t MASK = 1U << pin;
        
        if(0==(*reg_dir & MASK)) return false; // direction is input, 
        
        if (value)
            *reg_out |= (1U << pin);
        else
            *reg_out &= (~(1U << pin));
        return true;
    }
    
    bool gpio_read(uint8_t pin, bool* value) {
        if(pin>=MAX_PIN || !initialized || !value) return false;
        
        // read regardless of direction
        const uint32_t MASK = 1U << pin;
        *value = (0U != (*reg_in & MASK));
        
        return true;
    }
};

int main() {
    uintptr_t base = reinterpret_cast<uintptr_t>(new uint8_t[12]);
    bool output;
    memoryMappedGPIO *sensorGPIO = new memoryMappedGPIO;
    sensorGPIO->gpio_init(base);
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