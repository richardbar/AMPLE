#include "IndexOutOfRangeException.h"
#include "Memory.h"
#include "OutOfMemoryException.h"

#include <cstdlib>
#include <cstring>

Memory::Memory(uint64_t size)
{
    _size = size;

    _memory = (void*)malloc((size_t)_size);
    if (!_memory)
        throw OutOfMemoryException("Not enough memory to allocate");
    _memory = memset(_memory, 0, (size_t)_size);
    if (!_memory)
        throw OutOfMemoryException("Not enough memory to allocate");
}

void Memory::ResizeMemory(uint64_t size)
{
    _size = size;

    _memory = (void*)realloc(_memory, (size_t)_size);
    if (!_memory)
        throw OutOfMemoryException("Not enough memory to allocate");
}

void* Memory::Get(uint64_t pos)
{
    if (pos >= _size) throw IndexOutOfRangeException("");
    return (void*)((uint64_t)_memory + pos);
}

Memory::~Memory()
{
    free(_memory);
}
