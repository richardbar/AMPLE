#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "LineParser.h"
#include "OPCODE HANDLERS/V2.h"

bool HALT_V2(ARGS)
{
    if (instruction->numberOfArguments != 1)
    {
        fprintf(stderr, "HALT needs 1 arguments\n");
        return false;
    }

    binary->Arg1 = instruction->arguments[0].value;

    binary->Mode = 0;
    if (instruction->arguments[0].type == MEMORY)
    {
        binary->Mode |= 0b100;
    }
    else if (instruction->arguments[0].type == REGISTER)
    {
        binary->Mode |= 0b10;
    }
    else
    {
        binary->Mode |= 0b1;
    }

    binary->OpCode = 3;

    return true;
}