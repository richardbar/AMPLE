#pragma once

#include <stdbool.h>
#include <stdint.h>

#define NUMBER 0x01
#define REGISTER 0x02
#define MEMORY 0x04

struct Argument
{
    uint8_t* str;
    uint8_t type;
    int64_t value;

    bool(*IsRegister)(struct Argument);
    bool(*IsMemory)(struct Argument);
};

struct Instruction
{
    uint8_t* mnemonic;
    uint8_t numberOfArguments;
    struct Argument* arguments;

    bool(*AppendArgument)(struct Instruction, struct Argument*);
};

struct Binary
{
    uint32_t OpCode;
    uint32_t Mode;
    uint32_t Arg1;
    uint32_t Arg2;
    uint32_t Arg3;
};

struct Instruction* InitializeInstruction(uint8_t* mnemonic);
void FreeInstruction(struct Instruction*);

struct Argument* InitializeArgument(uint8_t* val);
void FreeArgument(struct Argument* argument);

struct Binary* AssembleLine(uint8_t* line);