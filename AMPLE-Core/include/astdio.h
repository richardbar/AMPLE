#ifndef __AMPLE_CORE_STDIO_H__
#define __AMPLE_CORE_STDIO_H__

#include "AMPLE.h"
#include "Memory.h"

#ifdef __cplusplus
extern "C"
{
#endif

EXPORT void Print(void* mem, void* reg);

EXPORT void OpenF(void* mem, void* reg);
EXPORT void CloseF(void* mem, void* reg);

#ifdef __cplusplus
}
#endif
#endif//__AMPLE_CORE_STDIO_H__