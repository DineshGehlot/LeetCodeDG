/******************************************************************************

Smart Pointer 

*******************************************************************************/

#include<iostream>

using namespace std;

template <typename T>

class SmartPtr{
    private:
        T* ptr;
        unsigned int* refCount = nullptr;
    public:
        void release() {
            if (refCount)
            {
                --(*refCount);
                if(*refCount == 0)
                {
                    delete ptr;
                    delete refCount;
                }
            }
        }
        
        // constructor
        SmartPtr(T* p=nullptr): ptr(p) {
            if(p == nullptr)
            {
                refCount = nullptr;
                return;
            }
            refCount = new unsigned int(1);
            cout << "Inside constructor: refCount =" << *refCount <<endl; 
            
        }
        // copy constructor
        SmartPtr(const SmartPtr& other): ptr(other.ptr) {
            refCount = other.refCount;
            *refCount += 1; 
            cout << "Inside copy constructor: refCount =" << *refCount <<endl;
        } 
        
        // destructor
        ~SmartPtr() {
            release();
            cout << "Inside destructor: refCount =" << *refCount <<endl;
        }
        
        int getRefCount() {
            return *refCount;
        }
};

int main()
{
    SmartPtr<int> s1 = new int(1);
    cout << s1.getRefCount() <<endl; // 1
    
    {
        SmartPtr<int> s2 = s1;
        cout << s1.getRefCount() <<endl; // 2
        
        cout << s2.getRefCount() <<endl; // 2
        SmartPtr<int> s3 = new int(5);
        cout << s2.getRefCount() <<endl; // 1
    
    }
    cout << s1.getRefCount() <<endl; //1
    
    return 0 ; 
    
}


// working but can be better, dreference etc. operator needed.