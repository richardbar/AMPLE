#ifndef __AMPLE_LIBRARIES_MEMORY_H__
#define __AMPLE_LIBRARIES_MEMORY_H__

#include <cstdint>

class Memory
{
public:
    static bool InitializeMemory(uint8_t ssize, uint64_t nsize);
    static bool ResizeMemory(uint64_t nsize);
    static void FreeMemory();
    static void* Get(uint64_t pos);
};

#endif//__AMPLE_LIBRARIES_MEMORY_H__