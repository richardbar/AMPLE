#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AMPLE.h"
#include "argProcessor.h"

#include "stdAMPLE.h"

#include "File.h"
#include "StringUtils.h"

#define PRINT_HELP()                                            \
    fprintf(stdout,                                             \
            "AMPLE Runtime\n"                                   \
            "Version: %s\n"                                     \
            "C Version Used: C%s",                              \
            __AMPLE_VERSION__,                                  \
            __AMPLE_C_VERSION__);

#define PRINT_VERSION()                                         \
    fprintf(stdout,                                             \
        "AMPLE Runtime\n"                                       \
        "Version: %s",                                          \
        __AMPLE_VERSION__);

bool HandleArgs(int argNum, char** argPtr, CList filesToRun, CList flags, int* _exitCode)
{
    if (argNum == 0)
    {
        fprintf(stderr, "No arguments passed to AMPLE");
        *_exitCode = 1;
        return false;
    }
    for (int i = 0; i < argNum; i++)
    {
        uint32_t sizeOfArgument = strlen(argPtr[i]);
        if (sizeOfArgument < 2)
            continue;

        if (argPtr[i][0] == '-')
        {
            if (argPtr[i][1] == '-' && sizeOfArgument > 3)
            {
                bool hasValue = false;
                char* argValue = NULL;
                for (uint32_t j = 0; true; j++)
                {
                    if (argPtr[i][j] == '\0')
                        break;
                    else if (argPtr[i][j] == '=')
                    {
                        hasValue = true;
                        argPtr[i][j] = '\0';
                        argValue = &(argPtr[i][j + 1]);
                        break;
                    }
                }

                if (strcmp("--help", argPtr[i]) == 0 && argNum != 1)
                {
                    fprintf(stderr, "--help needs to be the only argument");
                    *_exitCode = INVALID_ARGUMENT;
                    return false;
                }
                else if (strcmp("--help", argPtr[i]) == 0)
                {
                    PRINT_HELP();
                    *_exitCode = 0;
                    return false;
                }
                else if (strcmp("--version", argPtr[i]) == 0 && argNum != 1)
                {
                    fprintf(stderr, "--version needs to be the only argument");
                    *_exitCode = INVALID_ARGUMENT;
                    return false;
                }
                else if (strcmp("--version", argPtr[i]) == 0)
                {
                    PRINT_VERSION();
                    *_exitCode = 0;
                    return false;
                }
                else if (strcmp("--printRegisters", argPtr[i]) == 0)
                {
                    FlagStruct* flag = (FlagStruct*)malloc(sizeof(FlagStruct));
                    flag->FlagName = "printRegisters";
                    flag->FlagValue = NULL;
                    if (!InsertElementToList(flags, flag))
                        return false;
                }
                else if (strcmp("--notClearMemoryAndRegisters", argPtr[i]) == 0)
                {
                    FlagStruct* flag = (FlagStruct*)malloc(sizeof(FlagStruct));
                    flag->FlagName = "notClearMemoryAndRegisters";
                    flag->FlagValue = NULL;
                    if (!InsertElementToList(flags, flag))
                        return false;
                }
                else if (strcmp("--noWaitReturn", argPtr[i]) == 0)
                {
                    FlagStruct* flag = (FlagStruct*)malloc(sizeof(FlagStruct));
                    flag->FlagName = "noWaitReturn";
                    flag->FlagValue = NULL;
                    if (!InsertElementToList(flags, flag))
                        return false;
                }
                else if (strcmp("--memory", argPtr[i]) == 0)
                {
                    FlagStruct* flag = (FlagStruct*)malloc(sizeof(FlagStruct));
                    flag->FlagName = "memory";
                    flag->FlagValue = argValue;
                    if (!InsertElementToList(flags, flag))
                        return false;
                }
                else if (strcmp("--ampleBinaryVersion", argPtr[i]) == 0)
                {
                    FlagStruct* flag = (FlagStruct*)malloc(sizeof(FlagStruct));
                    flag->FlagName = "--ampleBinaryVersion";
                    flag->FlagValue = argValue;
                    if (!InsertElementToList(flags, flag))
                        return false;
                }
                else
                {
                    fprintf(stderr, "\"%s\" argument is not recognized\n", argPtr[i]);
                    *_exitCode = INVALID_ARGUMENT;
                    return false;
                }
            }
            else if (sizeOfArgument == 2)
            {
                if (argPtr[i][1] == 'h' && argNum != 1)
                {
                    fprintf(stderr, "-h needs to be the only argument");
                    *_exitCode = INVALID_ARGUMENT;
                    return false;
                }
                else if (argPtr[i][1] == 'h')
                {
                    PRINT_HELP();
                    *_exitCode = 0;
                    return false;
                }
                else if (argPtr[i][1] == 'v' && argNum != 1)
                {
                    fprintf(stderr, "-v needs to be the only argument");
                    *_exitCode = INVALID_ARGUMENT;
                    return false;
                }
                else if (argPtr[i][1] == 'v')
                {
                    PRINT_VERSION();
                    *_exitCode = 0;
                    return false;
                }
                else if (argPtr[i][1] == 'p')
                {
                    FlagStruct* flag = (FlagStruct*)malloc(sizeof(FlagStruct));
                    flag->FlagName = "printRegisters";
                    flag->FlagValue = NULL;
                    if (!InsertElementToList(flags, flag))
                        return false;
                }
                else if (argPtr[i][1] == 'c')
                {
                    FlagStruct* flag = (FlagStruct*)malloc(sizeof(FlagStruct));
                    flag->FlagName = "notClearMemoryAndRegisters";
                    flag->FlagValue = NULL;
                    if (!InsertElementToList(flags, flag))
                        return false;
                }
                else if (argPtr[i][1] == 'f')
                {
                    FlagStruct* flag = (FlagStruct*)malloc(sizeof(FlagStruct));
                    flag->FlagName = "noWaitReturn";
                    flag->FlagValue = NULL;
                    if (!InsertElementToList(flags, flag))
                        return false;
                }
                else
                {
                    fprintf(stderr, "\"%s\" argument is not recognized\n", argPtr[i]);
                    *_exitCode = INVALID_ARGUMENT;
                    return false;
                }
            }
            else
            {
                fprintf(stderr, "Argument is not recognizable");
                *_exitCode = INVALID_ARGUMENT;
                return false;
            }
        }
        else if (FileExists(argPtr[i]))
        {
            InsertElementToList(filesToRun, argPtr[i]);
        }
        else
        {
            fprintf(stderr, "Argument is not recognizable");
            *_exitCode = INVALID_ARGUMENT;
            return false;
        }
    }

    return true;
}

bool CListFlagEqual(void* flags, void* flagName)
{
    return StringEqual(((FlagStruct*)flags)->FlagName, flagName);
}

const char* GetCListFlagValue(CList flags, void* flagName)
{
    if (!ContainsValueInList(flags, flagName, CListFlagEqual))
        return NULL;

    for (uint32_t i = 0; i < GetSizeFromList(flags); i++)
    {
        if (CListFlagEqual(GetElementFromList(flags, i), flagName))
            return ((FlagStruct*)GetElementFromList(flags, i))->FlagValue;
    }
    return NULL;
}