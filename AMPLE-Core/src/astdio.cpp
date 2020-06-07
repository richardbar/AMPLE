#include "astdio.h"
#include "Memory.h"
#include "Register.h"

#include <cstdio>

#ifdef __cplusplus
extern "C"
{
#endif

void Print(void* mem, void* reg) {
    FILE* output = (*((bool*)(((Register*)reg)->Get(2)))) ? *((FILE**)(((Register*)reg)->Get(3))) : stdout;
    for (uint64_t i = *((uint64_t*)(((Register*)reg)->Get(1))); ; i++)
    {
        if ((*((char*)((Memory*)mem)->Get(i))) == '\0')
            break;
        fputc((int)(*((char*)((Memory*)mem)->Get(i))), output);
    }
}

#ifdef __cplusplus
}
#endif