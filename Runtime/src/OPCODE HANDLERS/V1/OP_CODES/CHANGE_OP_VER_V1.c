#include <stdbool.h>
#include <stdint.h>

#include "HandleOP.h"
#include "OPCODE HANDLERS/V1.h"

bool CHANGE_OP_VER_NUM(FUNCTION_ARGUMENTS)
{
    return SET_OPCODE_VERSION(Arg1);
}

bool CHANGE_OP_VER_REGISTER(FUNCTION_ARGUMENTS)
{
    uint32_t* pos = GetElementFromList(Registers, Arg1);
    if (!pos) return false;
    return SET_OPCODE_VERSION(*pos);
}

bool CHANGE_OP_VER_MEMORY(FUNCTION_ARGUMENTS)
{
    uint32_t* pos = GetElementFromList(Memory, Arg1);
    if (!pos) return false;
    return SET_OPCODE_VERSION(*pos);
}

bool (*CHANGE_OP_VER_MODES[])(ARGUMENT_TYPES) = {
        CHANGE_OP_VER_NUM,
        CHANGE_OP_VER_REGISTER,
        CHANGE_OP_VER_MEMORY
};

bool CHANGE_OP_VER_V1(MODE_FUNCTION_ARGUMENTS)
{
    return CHANGE_OP_VER_MODES[Mode](PASS_ARGUMENTS);
}