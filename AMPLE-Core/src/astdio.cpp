#include "astdio.h"
#include "Memory.h"
#include "Register.h"

#include <cstdio>

#ifdef __cplusplus
extern "C"
{
#endif

void Print(void* mem, void* reg) {
    fputs((const char*)(*((char*)((Memory*)mem)->Get(*((uint64_t*)(((Register*)reg)->Get(1)))))), (*((bool*)(((Register*)reg)->Get(2)))) ? *((FILE**)(((Register*)reg)->Get(3))) : stdout);

    // Removed because it did not print as fast as the method used above
    /* for (uint64_t i = *((uint64_t*)(((Register*)reg)->Get(1))); ; i++)
     * {
     *     if ((*((char*)((Memory*)mem)->Get(i))) == '\0')
     *         break;
     *     fputc((int)(*((char*)((Memory*)mem)->Get(i))), output);
     * }
     */
}

#ifdef __cplusplus
}
#endif