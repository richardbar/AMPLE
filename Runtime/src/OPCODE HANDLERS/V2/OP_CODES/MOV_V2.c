#include <stdbool.h>
#include <stdint.h>

#include "AMPLE.h"
#include "OPCODE HANDLERS/V2.h"

static uint32_t sizeOfRegisters = 0;

#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)

static bool MOV_NUM_REGISTER_N_N(FUNCTION_ARGUMENTS)
{
    CHECK_SIZE_OF_REGISTER();
    if (sizeOfRegisters <= Arg1)
        return false;
    return *((uint8_t*)GetElementFromList(Registers, Arg1)) = (uint8_t)Arg2;
}

static bool MOV_REGISTER_REGISTER_N_N(FUNCTION_ARGUMENTS)
{
    CHECK_SIZE_OF_REGISTER();
    if (sizeOfRegisters <= (Arg1 > Arg2) ? Arg1 : Arg2)
        return false;
    return *((uint8_t*)GetElementFromList(Registers, Arg1)) = *((uint8_t*)GetElementFromList(Registers, Arg2));
}

static bool MOV_REGISTER_REGISTER_F_N(FUNCTION_ARGUMENTS)
{
    return *((uint8_t*)GetElementFromList(Registers, Arg1)) = *((uint8_t*)GetElementFromList(Registers, Arg2));
}

static bool MOV_MEMORY_REGISTER_N_N(FUNCTION_ARGUMENTS)
{
    CHECK_SIZE_OF_REGISTER();
    CHECK_SIZE_OF_MEMORY();
    if (sizeOfRegisters <= Arg1 && sizeOfMemory <= Arg2)
        return false;
    return *((uint8_t*)GetElementFromList(Registers, Arg1)) = *((uint8_t*)GetElementFromList(Memory, Arg2));
}

static bool MOV_MEMORY_REGISTER_F_N(FUNCTION_ARGUMENTS)
{
    return *((uint8_t*)GetElementFromList(Registers, Arg1)) = *((uint8_t*)GetElementFromList(Memory, Arg2));
}

static bool MOV_NUM_MEMORY_N_N(FUNCTION_ARGUMENTS)
{
    CHECK_SIZE_OF_MEMORY();
    if (sizeOfMemory <= Arg1)
        return false;
    return *((uint8_t*)GetElementFromList(Memory, Arg1)) = (uint8_t)Arg2;
}

static bool MOV_REGISTER_MEMORY_N_N(FUNCTION_ARGUMENTS)
{
    CHECK_SIZE_OF_REGISTER();
    CHECK_SIZE_OF_MEMORY();
    if (sizeOfMemory <= Arg1 && sizeOfRegisters <= Arg2)
        return false;
    return *((uint8_t*)GetElementFromList(Memory, Arg1)) = *((uint8_t*)GetElementFromList(Registers, Arg2));
}

static bool MOV_REGISTER_MEMORY_F_N(FUNCTION_ARGUMENTS)
{
    return *((uint8_t*)GetElementFromList(Memory, Arg1)) = *((uint8_t*)GetElementFromList(Registers, Arg2));
}

static bool MOV_MEMORY_MEMORY_N_N(FUNCTION_ARGUMENTS)
{
    CHECK_SIZE_OF_MEMORY();
    if (sizeOfMemory <= (Arg1 > Arg2) ? Arg1 : Arg2)
        return false;
    return *((uint8_t*)GetElementFromList(Memory, Arg1)) = *((uint8_t*)GetElementFromList(Memory, Arg2));
}

static bool MOV_MEMORY_MEMORY_F_N(FUNCTION_ARGUMENTS)
{
    return *((uint8_t*)GetElementFromList(Memory, Arg1)) = *((uint8_t*)GetElementFromList(Memory, Arg2));
}


static bool (*MOV_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    SIXTEEN_NULL,
    MOV_NUM_REGISTER_N_N,
    MOV_REGISTER_REGISTER_N_N,
    MOV_REGISTER_REGISTER_F_N,
    MOV_MEMORY_REGISTER_N_N,
    MOV_MEMORY_REGISTER_F_N,
    MOV_NUM_MEMORY_N_N,
    MOV_REGISTER_MEMORY_N_N,
    MOV_REGISTER_MEMORY_F_N,
    MOV_MEMORY_MEMORY_N_N,
    MOV_MEMORY_MEMORY_F_N
};

bool MOV_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (MOV_MODES[Mode]) ? MOV_MODES[Mode](PASS_ARGUMENTS) : false;
}