#ifndef __AMPLE_LIBRARIES_REGISTER_H__
#define __AMPLE_LIBRARIES_REGISTER_H__

#include "Memory.h"

#include <cstdint>
#include <cstddef>

class Register : virtual public Memory
{
public:
    Register(uint64_t size);
    void ResizeMemory(uint64_t size);
    void* Get(uint64_t pos);
    ~Register();
};

#endif//__AMPLE_LIBRARIES_REGISTER_H__
