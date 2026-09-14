#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <stdio.h>
#include <iostream>

template <class T>
class UniquePtr {
    public:
        UniquePtr(T &p = nullptr) : mPtr {p}
        ~UniquePtr() {
            delete mPtr;
        }

    private:
        T* mPtr;
};

#endif
