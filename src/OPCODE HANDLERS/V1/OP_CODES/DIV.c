#include <stdbool.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V1.h"

bool DIV_REGISTER_NUM(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Registers) <= Arg1)
        return false;
    uint64_t* pos = GetElementFromList(Registers, Arg1);
    return *pos /= Arg2;
}

bool DIV_REGISTER_REGISTER(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Registers) <= (Arg1 < Arg2) ? Arg2 : Arg1)
        return false;
    uint64_t* pos1 = GetElementFromList(Registers, Arg1);
    uint64_t* pos2 = GetElementFromList(Registers, Arg2);
    return *pos1 /= *pos2;
}

bool DIV_REGISTER_MEMORY(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Registers) <= Arg1 || GetCapacityFromList(Memory) <= Arg2)
        return false;
    uint64_t* pos1 = GetElementFromList(Registers, Arg1);
    uint64_t* pos2 = GetElementFromList(Memory, Arg2);
    return *pos1 /= *pos2;
}

bool DIV_MEMORY_NUM(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= Arg1)
        return false;
    uint64_t* pos = GetElementFromList(Memory, Arg1);
    return *pos /= Arg2;
}

bool DIV_MEMORY_REGISTER(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= Arg1 || GetCapacityFromList(Registers) <= Arg2)
        return false;
    uint64_t* pos1 = GetElementFromList(Memory, Arg1);
    uint64_t* pos2 = GetElementFromList(Registers, Arg2);
    return *pos1 /= *pos2;
}

bool DIV_MEMORY_MEMORY(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= (Arg1 < Arg2) ? Arg2 : Arg1)
        return false;
    uint64_t* pos1 = GetElementFromList(Memory, Arg1);
    uint64_t* pos2 = GetElementFromList(Memory, Arg2);
    return *pos1 /= *pos2;
}

bool (*DIV_MODES[])(ARGUMENT_TYPES) = {
        DIV_REGISTER_NUM,
        DIV_REGISTER_REGISTER,
        DIV_REGISTER_MEMORY,
        DIV_MEMORY_NUM,
        DIV_MEMORY_REGISTER,
        DIV_MEMORY_MEMORY
};

bool DIV_V1(MODE_FUNCTION_ARGUMENTS)
{
    return DIV_MODES[Mode](PASS_ARGUMENTS);
}