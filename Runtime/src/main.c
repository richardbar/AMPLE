#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "File.h"

#include "argProcessor.h"


uint8_t endian = VOODOO_ENDIAN_D;
bool initialized = false;
bool* notClearMemory = NULL;
bool* printRegisters = NULL;

int32_t exitCode = -1;

int64_t* memorySize = NULL;


int GetEndian()
{
    char fNumber[] = { 0x01, 0x02, 0x03, 0x04,
                       0x05, 0x06, 0x07, 0x08 };
    uint64_t sNumber = 0x0102030405060708;

    if (*((uint64_t*)fNumber) == sNumber)
        return BIG_ENDIAN_D;
    else if (*((uint64_t*)fNumber) == ConvertEndianU64(sNumber))
        return LITTLE_ENDIAN_D;
    else
        return VOODOO_ENDIAN_D;
}

void HandleInitialization(int argc, char** argv)
{
    initialized = false;

    endian = GetEndian();
    if (endian == VOODOO_ENDIAN_D)
    {
        fprintf(stderr, "An unrecognized endian was captured");
        return;
    }

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

    NFileInitialize();

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

    NFileCleanUp();

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