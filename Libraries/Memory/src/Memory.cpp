#include "IndexOutOfRangeException.h"
#include "Memory.h"

#include <cstdlib>

void* memory = nullptr;
uint8_t posSize = 0;
size_t size = 0;

bool Memory::InitializeMemory(uint8_t ssize, uint64_t nsize)
{
    posSize = ssize;
    size = nsize;

    memory = (void*)malloc(posSize * size);
    return memory != nullptr;
}

bool Memory::ResizeMemory(uint64_t nsize)
{
    size = nsize;

    memory = (void*)realloc(memory, posSize * size);
    return memory != nullptr;
}

void Memory::FreeMemory()
{
    free(memory);
}

void* Memory::Get(uint64_t pos)
{
    if (pos >= size) throw IndexOutOfRangeException("");
    return (void*)((uint64_t)memory + pos * posSize);
}