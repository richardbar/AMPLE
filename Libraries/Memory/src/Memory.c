#include "Memory.h"

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void *memory;
    uint64_t size;
} MemoryStruct;

EXPORT _Bool MemoryInit(Memory* mem, uint64_t size) {
    MemoryStruct* memory = (MemoryStruct*)memory;
    if (memory)
        FreeMemory(memory);
    memory = (Memory*)malloc(sizeof(MemoryStruct));
    memory->memory = (void*)malloc(size);
    if (!memory->memory)
        return false;
    memory->memory = memset(memory->memory, 0, size);
    if (memory->memory)
        memory->size = size;
    return memory->memory != NULL;
}

EXPORT _Bool ResizeMemory(Memory* mem, uint64_t newSize) {
    MemoryStruct* memory = (MemoryStruct*)memory;
    if (!memory)
        return MemoryInit(memory, newSize);
    memory->memory = realloc(memory->memory, newSize);
    if (!memory->memory)
        return false;
    memory->size = newSize;
}

EXPORT void *GetMemoryPos(Memory* mem, uint64_t pos) {
    MemoryStruct* memory = (MemoryStruct*)mem;
    if (!(memory != NULL && memory->memory != NULL && memory->size > pos))
        return NULL;
    return (void*)((uint64_t)memory->memory + pos);
}

EXPORT void FreeMemory(Memory *mem) {
    MemoryStruct* memory = (MemoryStruct*)mem;
    if (memory->memory)
        free(memory->memory);
    if (mem)
        free(mem);
}

#ifdef __cplusplus
};
#endif