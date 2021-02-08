#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argProcessor.h"
#include "Execution.h"
#include "HandleOP.h"
#include "install.h"
#include "main.h"

#include "Instruction.h"

#include "File.h"
#include "CList.h"
#include "CStack.h"
#include "StringUtils.h"


CList FilesToRun = NULL;
CList Flags = NULL;
uint8_t* memory = NULL;
uint64_t* registers = NULL;
CList Memory = NULL;
CList Registers = NULL;

extern CStack ExecutionStack;

bool notClearMemoryAndRegisters = false;
bool printRegisters = false;
int64_t memorySize = 4096;

void HandleEnd(int _exitCode)
{
    fflush(stdout);
    fflush(stderr);

    FreeList(FilesToRun);
    FreeList(Flags);

    if (memory)
    {
        free(memory);
        memory = NULL;
    }
    if (registers)
    {
        free(registers);
        registers = NULL;
    }

    FreeList(Memory);
    FreeList(Registers);

    CleanArguments();

    exit(_exitCode);
}

bool InitializeMemoryAndRegisters(uint32_t registerSize)
{
    if (!Flags || !notClearMemoryAndRegisters || !memory || !registers)
    {
        if (memory)
        {
            free(memory);
            memory = NULL;
        }
        if (registers)
        {
            free(registers);
            registers = NULL;
        }

        memory = (uint8_t*)malloc(memorySize);
        if (!memory)
            return false;

        registers = (uint64_t*)malloc(registerSize * sizeof(uint64_t));
        if (!registers)
            return false;

        memset(memory, 0, memorySize);
        memset(registers, 0, registerSize * sizeof(uint64_t));
    }

    FreeList(Memory);
    FreeList(Registers);

    Memory = InitializeList(memorySize);
    if (!Memory)
        return false;
    Registers = InitializeList(registerSize);
    if (!Registers)
        return false;

    for (uint32_t i = 0; i < memorySize; i++)
    {
        if (!InsertElementToList(Memory, &memory[i]))
            return false;
    }
    for (uint32_t i = 0; i < registerSize; i++)
    {
        if (!InsertElementToList(Registers, &registers[i]))
            return false;
    }
    LockCapacityList(Registers);

    return true;
}

bool HandleFile(const char* fname, int* _exitCode)
{
    uint8_t* fileContent;
    uint64_t sizeOfFileContent;

    FILE* fptr = FileOpen(fname, FILE_READ | FILE_BINARY);
    sizeOfFileContent = FileReadWholeFile(fptr, &fileContent);
    FileClose(fptr);

    if (sizeOfFileContent % INSTRUCTION_LENGTH != 0)
    {
        *_exitCode = 1;
        free(fileContent);
        fileContent = NULL;
        return false;
    }

    if (!InitializeMemoryAndRegisters(64))
        return false;

    uint32_t numberOfInstructions = sizeOfFileContent / INSTRUCTION_LENGTH;
    struct ExecutionStruct* run = (struct ExecutionStruct*)malloc(sizeof(struct ExecutionStruct));
    run->ByteCode = fileContent;
    run->Position = 0;
    run->Size = numberOfInstructions;

    SET_OPCODE_VERSION(2);

    ExecutionStack = InitializeStack();
    InsertElementToStack(ExecutionStack, run);

    if (!Execute(Memory, Registers))
    {
        *_exitCode = 1;
        if (run)
        {
            free(run);
            run = NULL;
        }
        if (fileContent)
        {
            free(fileContent);
            fileContent = NULL;
        }
        return false;
    }

    if (run)
    {
        free(run);
        run = NULL;
    }
    if (fileContent)
    {
        free(fileContent);
        fileContent = NULL;
    }
    return true;
}

int main(int argc, char** argv)
{
    int exitCode = 0;

    FilesToRun = InitializeList(1);
    Flags = InitializeList(1);

    if (!HandleArgs(--argc, ++argv, &exitCode, &notClearMemoryAndRegisters, &printRegisters, &memorySize))
        HandleEnd(exitCode);

    /*if (ContainsValueInList(Flags, "install", CListFlagEqual))
    {
        const char* url = GetCListFlagValue(Flags, "url");
        const char* name = (GetCListFlagValue(Flags, "runtime")) ? GetCListFlagValue(Flags, "runtime") : GetCListFlagValue(Flags, "library");
        if (url == NULL || name == NULL)
        {
            fprintf(stderr, "url and runtime/library arguments are required when passing install argument to AMPLE");
            exitCode = 1;
            HandleEnd(exitCode);
        }
        if (!Download(
                (GetCListFlagValue(Flags, "runtime")) ? RUNTIME : LIBRARY,
                name,
                url
                ))
        {
            fprintf(stderr, "An unexpected error occurred while download from url");
            exitCode = 1;
            HandleEnd(exitCode);
        }
    }*/

    for (int i = 0; i < GetSizeFromList(FilesToRun); i++)
    {
        if (!FileExists(GetElementFromList(FilesToRun, i)))
        {
            fprintf(stdout, "File \"%s\" does not exist", (char*)GetElementFromList(FilesToRun, i));
            exitCode = 1;
            break;
        }

        if (!HandleFile(GetElementFromList(FilesToRun, i), &exitCode))
            break;
    }

    if (printRegisters && Registers)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                int64_t* regPtr = (int64_t*)GetElementFromList(Registers, i * 8 + j);
                if (!regPtr)
                {
                    printf("Error while printing registers\n");
                    return 1;
                }
                printf("%"PRId64" ", *regPtr);
            }
            printf("\n");
        }
    }

    HandleEnd((exitCode != 0) ? exitCode : *((int*)FastGetElementFromList(Registers, 0)));
}