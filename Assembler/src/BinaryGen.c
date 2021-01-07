#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BinaryGen.h"
#include "LineParser.h"
#include "OPCODE HANDLERS/V2.h"

int32_t TableSize = -1;

typedef struct
{
    const char* mnemonic;
    bool(*function)(struct Instruction*, struct Binary*);
} TableType;

TableType GenTable[] = {
        { "halt", HALT_V2 },
        { "HALT", HALT_V2 },
        { "mov", MOV_V2 },
        { "MOV", MOV_V2 },
        { "add", ADD_V2 },
        { "ADD", ADD_V2 },
        { "sub", SUB_V2 },
        { "SUB", SUB_V2 },
        { "mult", MULT_V2 },
        { "MULT", MULT_V2 },
        { "div", DIV_V2 },
        { "DIV", DIV_V2 },
        { "mod", MOD_V2 },
        { "MOD", MOD_V2 },
        { "lshift", LSHIFT_V2 },
        { "LSHIFT", LSHIFT_V2 },
        { "rshift", RSHIFT_V2 },
        { "RSHIFT", RSHIFT_V2 },
        { "and", AND_V2 },
        { "AND", AND_V2 },
        { "or", OR_V2 },
        { "OR", OR_V2 },
        { "xor", XOR_V2 },
        { "XOR", XOR_V2 },
        { "not", NOT_V2 },
        { "NOT", NOT_V2 }
};

static int64_t FindIndex(uint8_t* mnemonic)
{
    for (uint32_t i = 0; i < TableSize; i++)
    {
        if (strcmp(GenTable[i].mnemonic, (const char*)mnemonic) == 0)
            return i;
    }

    return -1;
}

bool Generate(struct Instruction* instruction, struct Binary* binary)
{
    if (TableSize == -1)
        TableSize = sizeof(GenTable) / sizeof(GenTable[0]);

    int64_t TablePosition = FindIndex(instruction->mnemonic);
    if (TablePosition == -1)
        return false;

    return GenTable[TablePosition].function(instruction, binary);
}