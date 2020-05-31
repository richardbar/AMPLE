#include "IndexOutOfRangeException.h"
#include "Register.h"
#include "OutOfMemoryException.h"

#include <cstdlib>
#include <cstring>

Register::Register(uint64_t size) : Memory(size * 8) { }

void Register::ResizeMemory(uint64_t size)
{
    _size = size;

    _memory = (void*)realloc(_memory, (size_t )_size * 8);
    if (!_memory)
        throw OutOfMemoryException("Not enough memory to allocate");
    _memory = memset(_memory, 0, (size_t)_size);
    if (!_memory)
        throw OutOfMemoryException("Not enough memory to allocate");
}

void* Register::Get(uint64_t pos)
{
    if (pos >= _size) throw IndexOutOfRangeException("");
    return (void*)((uint64_t)_memory + (pos * 8));
}

Register::~Register() { }
