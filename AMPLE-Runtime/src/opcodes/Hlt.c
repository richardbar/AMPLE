#include "opcodes/Hlt.h"
#include "AMPLE.h"

#include <stdio.h>

#if defined(__WINDOWS__)
    #include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
    #include <time.h>
#else
    #include <unistd.h>
#endif

#define FUNCTION_ARGUMENTS uint64_t arg1, uint64_t arg2, uint64_t arg3, Memory* memory, Memory* registers, uint32_t* programCounter

_Bool Hltms(FUNCTION_ARGUMENTS)
{
#ifdef __WINDOWS__
    Sleep(arga);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = arg1 / 1000;
    ts.tv_nsec = (arg1 % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(arg1 * 1000);
#endif
};

_Bool (*FunctionHltArray[])(FUNCTION_ARGUMENTS) = {
        Hltms
};

inline _Bool HltOP(uint32_t mode, FUNCTION_ARGUMENTS) {
    return FunctionHltArray[mode](arg1, arg2, arg3, memory, registers, programCounter);
}