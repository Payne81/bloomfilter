#pragma once 

#include <cstring>

#define SAFE_DELETE_ARRAY(ptr) \
    do {                       \
        if (nullptr != ptr) {  \
            delete[] ptr;      \
            ptr = nullptr;     \
        }                      \
    } while (0)
