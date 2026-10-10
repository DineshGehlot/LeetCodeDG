/******************************************************************************
Implement a custom template class SmartPtr<T> in C++ that behaves similarly to
std::shared_ptr<T> by maintaining a reference count for a dynamically allocated
object.

Multiple smart pointer instances should be able to share ownership of the same
object. The managed object must be deleted automatically when the last owning
smart pointer is destroyed or releases its ownership.

You must implement the reference-counting mechanism yourself. Do not use
std::shared_ptr internally.
*******************************************************************************/

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
        SmartPtr& operator=(const SmartPtr& other)
        {
            if (this == &other) return *this;
        
            release();
        
            ptr = other.ptr;
            refCount = other.refCount;
        
            if (refCount) ++(*refCount);

            return *this;
        }
        
        // Assignment Operator=
        SmartPtr& operator=(SmartPtr& other) {
            if (this == &other) return *this;
            
            release();
        
            ptr = other.ptr;
            refCount = other.refCount;
            *refCount += 1; 
            cout << "Inside Assignment operator: refCount =" << *refCount <<endl;
            return *this;
        }
        
        // destructor
        ~SmartPtr() {
            cout << "Inside destructor: refCount (before deletion) =" << *refCount <<endl;
            release();
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
        
        s3 = s1;
    
    }
    cout << s1.getRefCount() <<endl; //1
    
    
    
    return 0 ; 
    
}


// working but can be better, dreference etc. operator needed.