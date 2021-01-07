#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "LineParser.h"
#include "OPCODE HANDLERS/V2.h"

bool DIV_V2(ARGS)
{
    if (instruction->numberOfArguments != 2)
    {
        fprintf(stderr, "DIV needs 2 arguments\n");
        return false;
    }

    uint32_t length = 4;
    binary->Arg1 = instruction->arguments[0].value;
    binary->Arg2 = instruction->arguments[1].value;

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
        fprintf(stderr, "Argument 1, of MOV can not be a value\n");
        return true;
    }

    if (instruction->arguments[1].type == MEMORY)
    {
        binary->Mode |= 0b100000;
    }
    else if (instruction->arguments[1].type == REGISTER)
    {
        binary->Mode |= 0b10000;
    }
    else
    {
        binary->Mode |= 0b1000;
    }

    if (length == 2)
    {
        binary->Mode |= 0b1000000;
    }
    else if (length == 4)
    {
        binary->Mode |= 0b10000000;
    }
    else if (length == 8)
    {
        binary->Mode |= 0b100000000;
    }

    binary->OpCode = 7;

    return true;
}