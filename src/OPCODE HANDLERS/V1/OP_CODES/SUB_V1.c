#include <stdbool.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V1.h"

bool SUB_REGISTER_NUM(FUNCTION_ARGUMENTS)
{
    uint64_t* pos = GetElementFromList(Registers, Arg1);
    if (!pos)
        return false;
    return *pos -= Arg2;
}

bool SUB_REGISTER_REGISTER(FUNCTION_ARGUMENTS)
{
    uint64_t* pos1 = GetElementFromList(Registers, Arg1);
    uint64_t* pos2 = GetElementFromList(Registers, Arg2);
    if (!(pos1 && pos2))
        return false;
    return *pos1 -= *pos2;
}

bool SUB_REGISTER_MEMORY(FUNCTION_ARGUMENTS)
{
    uint64_t* pos1 = GetElementFromList(Registers, Arg1);
    uint64_t* pos2 = GetElementFromList(Memory, Arg2);
    if (!(pos1 && pos2))
        return false;
    return *pos1 -= *pos2;
}

bool SUB_MEMORY_NUM(FUNCTION_ARGUMENTS)
{
    uint64_t* pos = GetElementFromList(Memory, Arg1);
    if (!pos)
        return false;
    return *pos -= Arg2;
}

bool SUB_MEMORY_REGISTER(FUNCTION_ARGUMENTS)
{
    uint64_t* pos1 = GetElementFromList(Memory, Arg1);
    uint64_t* pos2 = GetElementFromList(Registers, Arg2);
    if (!(pos1 && pos2))
        return false;
    return *pos1 -= *pos2;
}

bool SUB_MEMORY_MEMORY(FUNCTION_ARGUMENTS)
{
    uint64_t* pos1 = GetElementFromList(Memory, Arg1);
    uint64_t* pos2 = GetElementFromList(Memory, Arg2);
    if (!(pos1 && pos2))
        return false;
    return *pos1 -= *pos2;
}

bool (*SUB_MODES[])(ARGUMENT_TYPES) = {
        SUB_REGISTER_NUM,
        SUB_REGISTER_REGISTER,
        SUB_REGISTER_MEMORY,
        SUB_MEMORY_NUM,
        SUB_MEMORY_REGISTER,
        SUB_MEMORY_MEMORY
};

bool SUB_V1(MODE_FUNCTION_ARGUMENTS)
{
    return SUB_MODES[Mode](PASS_ARGUMENTS);
}