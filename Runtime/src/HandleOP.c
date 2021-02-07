#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AMPLE.h"
#include "HandleOP.h"

#include "LibraryLoader.h"
#include "Instruction.h"


#define MAX_VERSIONS 512


bool (*OPCODE_HANDLER)(Instruction, uint32_t*, CList, CList) = NULL;

Library* VersionFilePointers = NULL;
bool (**Versions)(Instruction, uint32_t*, CList, CList) = NULL;


static bool LoadVersion(uint32_t VERSION)
{
    VersionFilePointers[VERSION] = LoadOPCodeVersion(VERSION);
    if (VersionFilePointers[VERSION] == NULL)
        return false;

    Versions[VERSION] = GetFuncFromLib(VersionFilePointers[VERSION], "HANDLE_OPCODE");
    if (Versions[VERSION] == NULL)
        return false;

    return true;
}


bool HANDLE_OPCODE(Instruction instruction, uint32_t* position, CList Memory, CList Registers)
{
    return (OPCODE_HANDLER) ? OPCODE_HANDLER(instruction, position, Memory, Registers) : false;
}

bool SET_OPCODE_VERSION(uint32_t INSTRUCTION_VERSION)
{
    if (Versions == NULL)
    {
        Versions = (bool(**)(Instruction, uint32_t*, CList, CList))malloc(MAX_VERSIONS * sizeof(bool(*)(Instruction, uint32_t*, CList, CList)));
        memset(Versions, 0, MAX_VERSIONS * sizeof(bool(*)(Instruction, uint32_t*, CList, CList)));

        VersionFilePointers = (Library*)malloc(MAX_VERSIONS * sizeof(Library));
        memset(VersionFilePointers, 0, MAX_VERSIONS * sizeof(Library));
    }

    if (INSTRUCTION_VERSION >= MAX_VERSIONS)
        return false;

    if (Versions[INSTRUCTION_VERSION] == NULL)
    {
        if (!LoadVersion(INSTRUCTION_VERSION))
            return false;
    }

    OPCODE_HANDLER = Versions[INSTRUCTION_VERSION];

    return true;
}