#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

#include "V2.h"

#if defined(__WINDOWS__)
    #include <Windows.h>
#elif (defined(__LINUX__) || defined(__APPLE__))
    #include <unistd.h>
#else
    #include <time.h>
#endif


static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)

static INLINE void Halt(uint64_t ms)
{
#if defined(__WINDOWS__)
    Sleep(ms);
#elif defined(__LINUX__) || defined(__APPLE__)
    clock_t endTime = clock() + ms;
    while (clock() < endTime) ;
#else

#endif
}

static bool HALT_NUM(FUNCTION_ARGUMENTS)
{
    Halt(Arg1);
    return true;
}
static bool HALT_REGISTER_N(FUNCTION_ARGUMENTS)
{
    CHECK_SIZE_OF_REGISTER();
    if (sizeOfRegisters <= Arg1)
        return false;
    Halt(*((uint64_t*)GetElementFromList(Registers, Arg1)));
    return true;
}
static bool HALT_REGISTER_F(FUNCTION_ARGUMENTS)
{
    Halt(*((uint64_t*)GetElementFromList(Registers, Arg1)));
    return true;
}
static bool HALT_MEMORY_N(FUNCTION_ARGUMENTS)
{
    CHECK_SIZE_OF_MEMORY();
    if (sizeOfMemory <= Arg1)
        return false;
    Halt(*((uint64_t*)GetElementFromList(Memory, Arg1)));
    return true;
}
static bool HALT_MEMORY_F(FUNCTION_ARGUMENTS)
{
    Halt(*((uint64_t*)GetElementFromList(Memory, Arg1)));
    return true;
}


static bool (*HALT_MODES[])(ARGUMENT_TYPES) = {
        NULL,
        HALT_NUM,                                                           // 0b0000000001
        HALT_REGISTER_N,                                                    // 0b0000000010
        HALT_REGISTER_F,                                                    // 0b0000000011
        HALT_MEMORY_N,                                                      // 0b0000000100
        HALT_MEMORY_F                                                       // 0b0000000101
};



bool HALT_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (HALT_MODES[Mode]) ? HALT_MODES[Mode](PASS_ARGUMENTS) : false;
}