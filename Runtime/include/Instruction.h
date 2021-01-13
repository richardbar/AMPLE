#pragma once

#include <stdint.h>

typedef struct
{
    uint32_t OpCode;
    uint32_t Mode;
    int64_t Arg1;
    int64_t Arg2;
    int64_t Arg3;
} Instruction;