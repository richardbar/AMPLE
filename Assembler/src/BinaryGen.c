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
        { "mov", MOV_V2 },
        { "MOV", MOV_V2 },
        { "add", ADD_V2 },
        { "ADD", ADD_V2 }
};

static int64_t FindIndex(uint8_t* mnemonic)
{
    for (uint32_t i = 0; i < TableSize; i++)
    {
        if (strcmp(GenTable[0].mnemonic, (const char*) mnemonic) == 0)
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