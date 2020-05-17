#ifndef __AMPLE_MEMORY_H__
#define __AMPLE_MEMORY_H__

#include <cstdint>

class Memory
{
public:
    static bool InitializeMemory();
    static bool ResizeMemory(int64_t tsize);
    static void FreeMemory();
};

#endif//__AMPLE_MEMORY_H__