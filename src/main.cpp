#include "UniquePtr.h"
#include <cassert>

int main() {
    // Special methods + get()
    UniquePtr<int> ptr(new int(5));
    UniquePtr<int> ptrNull;
    assert(ptrNull == nullptr);
    assert(*(ptr.get()) == 5);
    ptrNull = std::move(ptr);
    assert(*(ptrNull.get()) == 5);

    // Converting constructor template
    UniquePtr<int> tempPtr(new int(6));
    UniquePtr<int> rPtr(std::move(tempPtr));
    assert(*(rPtr.get()) == 6);

    // Operators
    UniquePtr<int> derefPtr(new int(7));
    int& reference = *derefPtr;
    assert(reference == 7);

    UniquePtr<int> nullPtr1;
    UniquePtr<int> nullPtr2;
    assert(nullPtr1 == nullPtr2);

    UniquePtr<int> truePtr1(new int(3));
    UniquePtr<int> falsePtr2;
    assert(bool(truePtr1));
    assert(bool(falsePtr2) == false);

    // Release
    UniquePtr<int> releasePtr1(new int(3));
    int* released = releasePtr1.release();
    assert(releasePtr1 == nullptr);
    assert(*released == 3);
    delete released;
    
    // Reset
    UniquePtr<int> resetPtr1(new int(3));
    resetPtr1.reset(new int(4));
    assert(*(resetPtr1.get()) == 4);

    // Swap
    UniquePtr<int> swapPtr1(new int(1));
    UniquePtr<int> swapPtr2(new int(2));
    swapPtr1.swap(swapPtr2);
    assert(*(swapPtr1.get()) == 2);
    assert(*(swapPtr2.get()) == 1);

    return 0;
}
