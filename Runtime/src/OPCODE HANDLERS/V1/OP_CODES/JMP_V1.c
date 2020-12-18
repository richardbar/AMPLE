#include <stdbool.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V1.h"


static bool JMP_NUM(FUNCTION_ARGUMENTS)
{
    return *position = Arg1 - 1;
}

static bool JMP_REGISTER(FUNCTION_ARGUMENTS)
{
    uint32_t* pos = GetElementFromList(Registers, Arg1);
    if (!pos) return false;
    return *position = *pos - 1;
}

static bool JMP_MEMORY(FUNCTION_ARGUMENTS)
{
    uint32_t* pos = GetElementFromList(Memory, Arg1);
    if (!pos) return false;
    return *position = *pos - 1;
}

static bool (*JMP_MODES[])(ARGUMENT_TYPES) = {
        JMP_NUM,
        JMP_REGISTER,
        JMP_MEMORY
};

bool JMP_V1(MODE_FUNCTION_ARGUMENTS)
{
    return JMP_MODES[Mode](PASS_ARGUMENTS);
}