#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argProcessor.h"


bool initialized = false;
bool* notClearMemory = NULL;
bool* printRegisters = NULL;

int32_t exitCode = -1;

int64_t* memorySize = NULL;


void HandleInitialization(int argc, char** argv)
{
    initialized = false;

    notClearMemory = (bool*)malloc(sizeof(bool));
    if (!notClearMemory)
        return;

    printRegisters = (bool*)malloc(sizeof(bool));
    if (!printRegisters)
        return;

    memorySize = (int64_t*)malloc(sizeof(int64_t));
    if (!memorySize)
        return;

    HandleArgs(argc, argv, &exitCode, notClearMemory, printRegisters, memorySize);

    initialized = true;
}

void HandleCleanup()
{
    if (notClearMemory)
    {
        free(notClearMemory);
        notClearMemory = NULL;
    }

    if (!printRegisters)
    {
        free(printRegisters);
        printRegisters = NULL;
    }

    if (!memorySize)
    {
        free(memorySize);
        memorySize = NULL;
    }

    CleanArguments();
}

void ExitAMPLE()
{
    exit(exitCode);
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "AMPLE-Runtime needs at least one argument");
        exitCode = -1;
        HandleCleanup();
        ExitAMPLE();
    }

    argc--;
    argv++;

    HandleInitialization(argc, argv);
    if (!initialized)
    {
        exitCode = -1;
        HandleCleanup();
        ExitAMPLE();
    }



    exitCode = 0;
    HandleCleanup();
    ExitAMPLE();
}