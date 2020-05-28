#ifndef __AMPLE_LIBRARIES_MEMORY_H__
#define __AMPLE_LIBRARIES_MEMORY_H__

#include "AMPLE.h"
#include <cstdint>

class Memory
{
protected:
    void* _memory;
    size_t _size;
public:
    EXPORT explicit Memory(size_t size);
    EXPORT virtual void ResizeMemory(size_t size);
    EXPORT virtual void* Get(uint64_t pos);
    EXPORT virtual ~Memory();
};

#endif//__AMPLE_LIBRARIES_MEMORY_H__
