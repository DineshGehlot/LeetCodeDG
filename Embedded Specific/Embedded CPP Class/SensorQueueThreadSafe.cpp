/******************************************************************************

You are working on an embedded automotive system.

A hardware sensor produces measurements asynchronously. The hardware writes
sensor events into a memory-mapped FIFO. The hardware raises an interrupt
whenever new data is available.

There may be multiple producers/sensors, but only one processing thread consumes events.

You need to implement the software side.

ISR
 |
 +--> Sensor processing thread
          |
          +--> consumers

Assume:
* push() may be called from an interrupt context.
* pop() is called from a normal thread.
* Dynamic memory allocation is not allowed.
* The queue must have a fixed capacity.
* If the queue is full, push() should fail rather than overwrite an existing event.
* The implementation should be efficient enough for a high-frequency sensor.

*******************************************************************************/
#include<cstdint>
#include<cstdlib>
//#include<iostream>
#include<mutex>

using namespace std;

struct SensorEvent {
    uint32_t sensorId;
    uint64_t timestamp;
    int32_t  value;
};

class sensorEventQueue {
    uint64_t qSize, front, rear, currLoad;
    struct SensorEvent *sensorQ;
    mutex mtx;
public:
    
    sensorEventQueue(struct SensorEvent *sQ, uint64_t n): qSize(n), sensorQ(sQ) {
        if(!sQ) qSize = 0;
        front = rear = currLoad = 0;
        //cout << "Queue intiated with size: " << qSize <<endl;   
    }
    
    bool push (const SensorEvent& event) {  
    // this call is from ISR, and a lock can cause deadlock, in RTOS will use message to diffrent thread to handle push operation
        mtx.lock();
        if(qSize ==0) {
            //cout << "No Queue Buffer" <<endl; 
            return false;
        }
        if (currLoad == qSize) {
           // cout << "Queue Full" <<endl; 
            return false;
        }
        sensorQ[front] = event;
        ++currLoad;
        front = (front + 1) % qSize;
        mtx.unlock();
        return true;
    }
    
    bool pop(SensorEvent& event) {
        mtx.lock();
        if (currLoad == 0)
        //if(front == rear)
        {
            //cout << "Queue Empty" <<endl;
            return false;
        }
        --currLoad;
        event = sensorQ[rear];
        rear = (rear + 1) % qSize;
        mtx.unlock();
        return true;
        
    }
    
    size_t size() const {
        return currLoad; // this should also be a critical section
    }
};


int main() {
    struct SensorEvent test[5];
    sensorEventQueue *eQ = new sensorEventQueue(test, 4);
    for (int i = 0; i < 6; ++i) {
        eQ->push(test[i]);
    }
    for (int i = 0; i < 6; ++i) {
        eQ->pop(test[i]);
    }
    return 0;
}