#ifndef __AMPLE_LIBRARIES_MEMORY_H__
#define __AMPLE_LIBRARIES_MEMORY_H__

#include <cstdint>

#if defined(_MSC_VER)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

class Memory
{
public:
    EXPORT static bool InitializeMemory(uint8_t ssize, size_t nsize);
    EXPORT static bool ResizeMemory(size_t nsize);
    EXPORT static void FreeMemory();
    EXPORT static void* Get(uint64_t pos);
};

#endif//__AMPLE_LIBRARIES_MEMORY_H__