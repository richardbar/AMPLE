#include <stdbool.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V1.h"

bool MOV_NUM_TO_REGISTER(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Registers) <= Arg1)
        return false;
    uint64_t* pos = GetElementFromList(Registers, Arg1);
    if (!pos)
        return false;
    return *pos = Arg2;
}

bool MOV_REGISTER_TO_REGISTER(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Registers) <= (Arg1 < Arg2) ? Arg2 : Arg1)
        return false;
    uint64_t* pos1 = GetElementFromList(Registers, Arg1);
    uint64_t* pos2 = GetElementFromList(Registers, Arg2);
    if (!(pos1 && pos2))
        return false;
    return *pos1 = *pos2;
}

bool MOV_MEMORY_TO_REGISTER(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= Arg1 || GetCapacityFromList(Registers) <= Arg2)
        return false;
    uint64_t* pos1 = GetElementFromList(Memory, Arg1);
    uint64_t* pos2 = GetElementFromList(Registers, Arg2);
    if (!(pos1 && pos2))
        return false;
    return *pos1 = *pos2;
}

bool MOV_NUM_TO_MEMORY(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= Arg2)
        return false;
    uint64_t* pos = GetElementFromList(Memory, Arg1);
    if (!pos)
        return false;
    return *pos = Arg2;
}

bool MOV_REGISTER_TO_MEMORY(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= Arg2 || GetCapacityFromList(Registers) <= Arg1)
        return false;
    uint64_t* pos1 = GetElementFromList(Registers, Arg1);
    uint64_t* pos2 = GetElementFromList(Memory, Arg2);
    if (!(pos1 && pos2))
        return false;
    return *pos1 = *pos2;
}

bool MOV_MEMORY_TO_MEMORY(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= (Arg1 < Arg2) ? Arg2 : Arg1)
        return false;
    uint64_t* pos1 = GetElementFromList(Memory, Arg1);
    uint64_t* pos2 = GetElementFromList(Memory, Arg2);
    if (!(pos1 && pos2))
        return false;
    return *pos1 = *pos2;
}

bool (*MOV_MODES[])(ARGUMENT_TYPES) = {
        MOV_NUM_TO_REGISTER,
        MOV_REGISTER_TO_REGISTER,
        MOV_MEMORY_TO_REGISTER,
        MOV_NUM_TO_MEMORY,
        MOV_REGISTER_TO_MEMORY,
        MOV_MEMORY_TO_MEMORY
};

bool MOV_V1(MODE_FUNCTION_ARGUMENTS)
{
    return MOV_MODES[Mode](PASS_ARGUMENTS);
}