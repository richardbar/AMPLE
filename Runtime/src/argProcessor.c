#if defined(_MSC_VER)
    #define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AMPLE.h"
#include "argProcessor.h"

#include "stdAMPLE.h"

#include "ArgumentParser.h"
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

ArgumentType argsTypes[] = {
        { .longType = "help", .shortType = "h", .isOnlyArgument = true, .hasValue = false },
        { .longType = "version", .shortType = NULL, .isOnlyArgument = true, .hasValue = false },
        { .longType = "force", .shortType = NULL, .isOnlyArgument = false, .hasValue = false },
        { .longType = "printRegisters", .shortType = "p", .isOnlyArgument = false, .hasValue = false },
        { .longType = "notClearMemoryAndRegisters", .shortType = "c", .isOnlyArgument = false, .hasValue = false },
        { .longType = "memory", .shortType = NULL, .isOnlyArgument = false, .hasValue = true },
        { .longType = "AMPLEBinaryVersion", .shortType = NULL, .isOnlyArgument = false, .hasValue = true },
        { .longType = "install", .shortType = "i", .isOnlyArgument = false, .hasValue = false },
        { .longType = "runtime", .shortType = NULL, .isOnlyArgument = false, .hasValue = true },
        { .longType = "url", .shortType = NULL, .isOnlyArgument = false, .hasValue = true },
};

bool HandleArgs(int argNum, char** argPtr, int32_t* _exitCode, bool* notClearMemoryAndRegisters, bool* printRegisters, int64_t* memorySize)
{
    if (argNum == 0)
    {
        fprintf(stderr, "No arguments passed to AMPLE");
        *_exitCode = 1;
        return false;
    }

    if (!InitializeArgumentParser())
    {
        fprintf(stderr, "Error while initializing argument parser\n");
        return false;
    }

    if (!AddArgumentTypes(&(argsTypes[0]), sizeof(argsTypes) / sizeof(argsTypes[0])))
    {
        fprintf(stderr, "Error adding Argument Types to Argument parser\n");
        return false;
    }
    if (!ParseArguments(argPtr, argNum, false))
    {
        fprintf(stderr, "Error parsing arguments\n");
        return false;
    }

    if (ContainsArgument("help"))
    {
        PRINT_HELP();
        *_exitCode = 0;
        return false;
    }
    if (ContainsArgument("version"))
    {
        PRINT_VERSION();
        *_exitCode = 0;
        return false;
    }
    if (ContainsArgument("notClearMemoryAndRegisters"))
        *notClearMemoryAndRegisters = true;
    if (ContainsArgument("printRegisters"))
        *printRegisters = true;
    if (ContainsArgument("memory"))
    {
        int64_t memory;
        GetArgumentValueINT64("memory", &memory);
        if (memory < 0)
        {
            fprintf(stderr, "Memory argument can not be negative\n");
            *_exitCode = 1;
            return false;
        }

        *memorySize = memory;
    }

    return true;
}

void CleanArguments()
{
    CleanupArgumentParser();
}