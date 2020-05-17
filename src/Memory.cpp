#include "Memory.h"

#include <cstdlib>

void* memory;
size_t* size;

bool Memory::InitializeMemory()
{
    size = (size_t*)malloc(1 * sizeof(size_t));
    if (!size) return false;
    *size = 1;
    memory = malloc(*size);
    return (memory != nullptr);
}

bool Memory::ResizeMemory(int64_t tsize)
{
    *size = tsize;
    memory = realloc(memory, *size);
    return (memory != nullptr);
}

void Memory::FreeMemory()
{
    free(size);
    free(memory);
}