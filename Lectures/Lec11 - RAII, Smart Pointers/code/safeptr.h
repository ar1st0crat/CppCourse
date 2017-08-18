#pragma once

template <class T>
class SafePtr
{
public:
    explicit SafePtr(T* p) : ptr_(p)
    {
    }

    ~SafePtr()
    {
        delete ptr_;
    }

    T* get()
    {
        if (!ptr_) throw 0;		// throw BadPointer
        return ptr_;
    }

    T& operator*()
    {
        return *get();
    }

    T* operator->()
    {
        return get();
    }

private:
    T* ptr_;

private:
    SafePtr(const SafePtr& p);
    SafePtr& operator=(const SafePtr& p);
};
