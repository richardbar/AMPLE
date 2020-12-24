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
bool HandleArgs(int argNum, char** argPtr, CList filesToRun, CList flags, int* _exitCode);

/**
 * @param flags CList pointer to check if name is equal
 * @param flagName String of the flag to look for
 * @return Returns true if flag is equal to flagName and false if it does not
 */
bool CListFlagEqual(void* flags, void* flagName);

const char* GetCListFlagValue(CList flags, void* flagName);