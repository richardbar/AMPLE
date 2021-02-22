#pragma once

#include <stdbool.h>

#include "AMPLE.h"
#include "CList.h"

typedef struct
{
    char* FlagName;
    char* FlagValue;
} FlagStruct;

/**
 * @param argNum argNum Number of arguments to be parsed
 * @param argPtr Pointer to array of string pointers to be parsed
 * @param filesToRun CList that files to be run will be put in
 * @param flags CList that flags will be placed in
 * @param _exitCode Int Exit code pointer.
 * @return Returns true if program can continue and false if not
 */
bool HandleArgs(int argNum, char** argPtr, int32_t* _exitCode, bool* notClearMemoryAndRegisters, bool* printRegisters, int64_t* memorySize);

/**
 * Clean up Arguments from library.
 */
void CleanArguments();