/******************************************************************************

Implement a Thread-Safe Single-Producer, Single-Consumer (SPSC) Ring Buffer

Problem statement: Implement a fixed-size ring buffer in C for a UART driver
with the following requirements:
1. The buffer stores bytes (uint8_t).
2. The buffer size is 256 bytes.
3. One producer writes bytes, and one consumer reads bytes concurrently.
4. The producer may run in an ISR, while the consumer runs in a task.
5. The buffer must distinguish between full and empty states correctly.
6. No dynamic memory allocation is allowed.
7. push() must fail if the buffer is full.
8. pop() must fail if the buffer is empty.
9. The implementation must avoid data races and ensure correct synchronization between the producer and consumer.

Implement these functions:
```
#define RING_BUFFER_SIZE 256

typedef struct {
    // Define your members here
} ring_buffer_t;

void ring_buffer_init(ring_buffer_t *rb);

bool ring_buffer_push(ring_buffer_t *rb, uint8_t data);

bool ring_buffer_pop(ring_buffer_t *rb, uint8_t *data);
```

*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>


#define RING_BUFFER_SIZE 256

typedef struct {
    uint32_t front, rear, count;
    uint8_t buffer[RING_BUFFER_SIZE];
} ring_buffer_t;


void ring_buffer_init(ring_buffer_t *rb) {
    rb->count = 0;
    rb->front = rb->rear = 0;
}
// Can be called in ISR context
bool ring_buffer_push(ring_buffer_t *rb, uint8_t data) {
    if (rb->count == RING_BUFFER_SIZE) return false;
    rb->buffer[rb->front] = data;
    rb->front = (rb->front+1)%RING_BUFFER_SIZE;
    rb->count++;
    return true;
}


bool ring_buffer_pop(ring_buffer_t *rb, uint8_t *data) {
    //__irq_lock(); 
    // __irq_lock() ensures that no interrupt will be handled while executing this.
    // Means no producer calls while executiong this.
    bool status = false;
    if(rb->count) {
        *data = rb->buffer[rb->rear];
        rb->rear = (rb->rear+1)%RING_BUFFER_SIZE;
        rb->count--;
        status = true;
    }
    //__irq_unlock();
    return status;
}

int main() {
    bool status;
    uint8_t data;
    ring_buffer_t rb;
    ring_buffer_init(&rb);
    status = ring_buffer_push(&rb,8);
    if(!status) printf("buffer full\n");
    status = ring_buffer_pop(&rb,&data);
    if(!status) printf("buffer empty\n");
    return 0;
}

// The implementation is good for SPSC (single producer, single consumer),
// check SensorQueueThreadSafe.cpp for non SPSC cases