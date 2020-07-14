#ifndef __AMPLE_LIBRARIES_MEMORY_H__
#define __AMPLE_LIBRARIES_MEMORY_H__

#include "AMPLE.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *Memory;
EXPORT _Bool MemoryInit(Memory* mem, uint64_t size);
EXPORT _Bool ResizeMemory(Memory* mem, uint64_t newSize);
EXPORT void *GetMemoryPos(Memory* mem, uint64_t pos);
EXPORT void FreeMemory(Memory* mem);

#ifdef __cplusplus
};
#endif

#endif//__AMPLE_LIBRARIES_MEMORY_H__