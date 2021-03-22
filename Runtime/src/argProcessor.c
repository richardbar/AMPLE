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
        { .longType = "install", .shortType = "i", .isOnlyArgument = false, .hasValue = false },
        { .longType = "runtime", .shortType = NULL, .isOnlyArgument = false, .hasValue = true },
        { .longType = "url", .shortType = NULL, .isOnlyArgument = false, .hasValue = true },
};

uint32_t CurrentFile = 0;
int64_t MaxFiles = -1;

bool HandleArgs(int argNum, char** argPtr, int32_t* _exitCode, bool* notClearMemoryAndRegisters, bool* printRegisters, int64_t* memorySize)
{
    if (argNum == 0)
    {
        fprintf(stderr, "No arguments passed to AMPLE");
        *_exitCode = 1;
        return false;
    }

    if (!ArgumentParserInitialize())
    {
        fprintf(stderr, "Error while initializing argument parser\n");
        return false;
    }

    if (!ArgumentParserAddArgumentTypes(argsTypes, sizeof(argsTypes) / sizeof(argsTypes[0])))
    {
        fprintf(stderr, "Error adding Argument Types to Argument parser\n");
        return false;
    }
    if (!ArgumentParserParseArguments(argPtr, argNum, false))
    {
        fprintf(stderr, "Error parsing arguments\n");
        return false;
    }

    if (ArgumentParserContainsArgument("help"))
    {
        PRINT_HELP();
        *_exitCode = 0;
        return false;
    }
    if (ArgumentParserContainsArgument("version"))
    {
        PRINT_VERSION();
        *_exitCode = 0;
        return false;
    }
    if (ArgumentParserContainsArgument("notClearMemoryAndRegisters"))
        *notClearMemoryAndRegisters = true;
    if (ArgumentParserContainsArgument("printRegisters"))
        *printRegisters = true;
    if (ArgumentParserContainsArgument("memory"))
    {
        int64_t memory;
        ArgumentParserGetArgumentValueINT64("memory", &memory);
        if (memory < 0)
        {
            fprintf(stderr, "Memory argument can not be negative\n");
            *_exitCode = 1;
            return false;
        }

        *memorySize = memory;
    }

    MaxFiles = ArgumentParserGetNumberOfFiles();

    return true;
}

int32_t GetNextFile(char** fname) {
    if (MaxFiles < 0)
        return -1;

    if (CurrentFile >= MaxFiles)
        return -1;

    uint32_t fileNameSize = ArgumentParserGetFileNameLength(CurrentFile);
    *fname = (char*)malloc((fileNameSize + 1) * sizeof(char));
    if (!*fname)
        return -1;
    memset(*fname, 0, (fileNameSize + 1) * sizeof(char));
    ArgumentParserGetFileName(CurrentFile++, *fname, fileNameSize);
    return fileNameSize;
}

void CleanArguments()
{
    ArgumentParserCleanup();
}