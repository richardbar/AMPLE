#include "astdio.h"
#include "Memory.h"

#include <cstdio>

#ifdef __cplusplus
extern "C"
{
#endif

void Print(void* mem, void* reg) {
    Memory* memory = (Memory*)mem;
    Memory* registers = (Memory*)reg;
    FILE* output = (*((_Bool*)GetMemoryPos(registers, 2))) ? *((FILE**)GetMemoryPos(registers, 3)) : stdout;
    for (uint64_t i = *(uint64_t*)GetMemoryPos(registers, 1); ; i++)
    {
        if (*((char*)GetMemoryPos(memory, i)) == '\0')
            break;
        fputc((int)(*((char*)GetMemoryPos(memory, i))), output);
    }
}

void OpenF(void* mem, void* reg) {
    Memory* memory = (Memory*)mem;
    Memory* registers = (Memory*)reg;
    uint64_t nameOfFile = *(uint64_t*)GetMemoryPos(registers, 2);
    const char* mode = (*(_Bool*)GetMemoryPos(registers, 3)) ? "w" : "r";
    FILE* fptr = fopen((const char*)GetMemoryPos(memory, nameOfFile), mode);
    *(FILE**)GetMemoryPos(registers, 1) = fptr;
}

void CloseF(void* mem, void* reg) {
    Memory* registers = (Memory*)registers;
    fclose(*(FILE**)GetMemoryPos(registers, 1));
}

#ifdef __cplusplus
}
#endif