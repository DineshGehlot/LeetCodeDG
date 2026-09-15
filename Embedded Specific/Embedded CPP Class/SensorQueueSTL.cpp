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

*******************************************************************************/
#include<cstdint>
#include<cstdlib>
#include<queue>
#include<iostream>

using namespace std;

struct SensorEvent {
    uint32_t sensorId;
    uint64_t timestamp;
    int32_t  value;
};

class sensorEventQueue {
    uint64_t qSize, currLoad;
    queue<struct SensorEvent> sensorQ;
public:
    
    sensorEventQueue(uint64_t n=100): qSize(n), currLoad(0) {
        cout << "Queue intiated with size: " << n <<endl;   
    }
    
    bool push (const SensorEvent& event) {
        if(currLoad == qSize) {
            cout << "Queue Full" <<endl; 
            return false;
        }
        ++currLoad;
        sensorQ.push(event);
        return true;
    }
    
    bool pop(SensorEvent& event) {
        if(sensorQ.empty())
        {
             cout << "Queue Empty" <<endl;
            return false;
        }
        --currLoad;
        event = sensorQ.front();
        sensorQ.pop();
        return true;
    }
    
    size_t size() const {
        return sensorQ.size();
    }
};


int main() {
    sensorEventQueue *eQ = new sensorEventQueue(4);
    struct SensorEvent test[5];
    for (int i = 0; i < 6; ++i) {
        eQ->push(test[i]);
    }
    for (int i = 0; i < 6; ++i) {
        eQ->pop(test[i]);
    }
    return 0;
}