#ifndef __AMPLE_LIBRARIES_MEMORY_H__
#define __AMPLE_LIBRARIES_MEMORY_H__

#include "AMPLE.h"
#include <cstdint>

class Memory
{
protected:
    void* _memory;
    uint64_t _size;
public:
    EXPORT explicit Memory(uint64_t size);
    EXPORT virtual void ResizeMemory(uint64_t size);
    EXPORT virtual void* Get(uint64_t pos);
    EXPORT virtual ~Memory();
};

#endif//__AMPLE_LIBRARIES_MEMORY_H__
