/******************************************************************************

Synchronization Primitives:
Mutex, semaphore, Spinlock, Atomic variables

*******************************************************************************/
#include <iostream>
#include <semaphore>
#include <mutex>
#include <atomic>

using namespace std;

int main()
{
    binary_semaphore semB(1); // Initial value, 1 Free, 0 lock
    // binary_semaphore is same as counting_semaphore<1>
    counting_semaphore<2> semC(2); // <MinAllowed>, (Intial value)
    mutex mtx;
    atomic_uint sig;
    
    
    semB.acquire();
    
    semC.release(); // Count value = 3
    semC.acquire(); // Count value = 2
    
    semC.acquire(); // Count value = 1
    semC.acquire(); // Count value = 0
    mtx.lock();
    atomic_store(&sig, 0); // lock it
    
    
    // Spinlock loop & atomic operations.
    while(1) {
        // for failure case, FREE will be updated as current value of signal
        // so we have to udpate FREE before calling atomic_compare_exchange_weak.
        uint32_t FREE = 1; // 1 Free, 0 lock
        if (atomic_compare_exchange_weak(&sig,&FREE,0)) break; // object, expected, desired_value to be updated
        cout << "[Lock is not acquire yet] Loop while, sig != free " <<endl;
        cout << "Free became " <<FREE <<endl;
        
        // this should not be part of spinlock loop,
        // relesing lock to break loop, assume its done on some other core.
        atomic_store(&sig, 1); // unlock the spinlock.
    }
    cout << "spinlock acquired; current lock value is " << atomic_load(&sig) <<endl;
    
    
    mtx.unlock();
    semC.release(); // Count value = 1
    semC.release(); // Count value = 2
    semB.release(); 

    return 0;
}
/*
Key Points:
1. Use mutex for critical sections that need to be held for extended periods. (strict owernship needed)
2. For producer consumer problem use semaphores. (No owernship needed).
3. Never block while holding spinlock. Use IRQ masking if required. 
4. Use atomic operations for simple shared data access. like spinlock internal lock.
5. IRQ handler should have minimum code and should not block.
6. Use sequence ordering of locks:
    semaphore_acquire(current_task); // Acquire current semaphore first
    mutex.lock(); // or priority inherited mutex LOCK
    irq_disable(); // Or irq_contex_save();
    spinlock_lock(&spinlock);
    
    // The critical section

    spinlock_unlock(&spinlock);
    irq_enable(); // Or irq_contex_restore();
    mutex.unlock(); // or priority inherited mutex UNLOCK
    semaphore_release(subsequrent_task); // Release subsequent task semaphore
*/

