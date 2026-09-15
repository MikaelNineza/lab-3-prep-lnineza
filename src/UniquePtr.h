#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <stdio.h>
#include <iostream>
#include <utility>

template <class T>
class UniquePtr {
    public:
        template <class U> friend class UniquePtr;

        UniquePtr(T* p = nullptr) : mPtr(p) {}

        UniquePtr(const UniquePtr<T>& other) = delete;

        UniquePtr(UniquePtr<T>&& other) {
            mPtr = other.release();
        }

        template <class U>
        UniquePtr(UniquePtr<U>&& other) {
            mPtr = other.release();
        }

        ~UniquePtr() {
            delete mPtr;
        }

        T& operator*() const {return *mPtr;}

        UniquePtr<T>& operator=(const UniquePtr<T>& other) = delete;

        UniquePtr<T>& operator=(UniquePtr<T>&& other) {
            if (this != &other) {
                delete mPtr;
                mPtr = other.release();
            }
            return *this;
        }

        T* operator->() const {return mPtr;}

        T* get() const { return mPtr;}

        bool operator==(const UniquePtr<T>& other) const {return mPtr == other.mPtr;}

        T* release() {
            T* p = mPtr;
            mPtr = nullptr;
            return p;
        }

        void reset(T* newPtr = nullptr) {
            delete mPtr;
            mPtr = newPtr;
        }

        void swap(UniquePtr<T>& other) {
            T* tempT = mPtr;
            mPtr = other.mPtr;
            other.mPtr = tempT;
        }

        operator bool() const {return mPtr != nullptr;}

    private:
        T* mPtr;
};

template <class T, class... Args>
    UniquePtr<T> makeUnique(Args&&... args)
    {
        T* p = new T(std::forward<Args>(args)...);
        UniquePtr<T> ptr(p);
        return ptr;
    }

#endif
