#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

#include "AMPLE.h"
#include "argProcessor.h"
#include "HandleOP.h"

#include "file.h"
#include "List.h"

#if (defined(__LINUX__) || defined(__APPLE__))
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

List FilesToRun = NULL;
List Flags = NULL;
uint8_t* memory = NULL;
uint64_t* registers = NULL;
List Memory = NULL;
List Registers = NULL;

bool stringComparer(void* str1, void* str2)
{
    return strcmp(str1, str2) == 0;
}

void HandleEnd(int _exitCode)
{
    fflush(stdout);
    fflush(stderr);

    putc('\n', stdout);

    fflush(stdout);
    fflush(stderr);

    FreeList(FilesToRun);
    FreeList(Flags);

    if (memory)
        free(memory);
    if (registers)
        free(registers);

    FreeList(Memory);
    FreeList(Registers);

    exit(_exitCode);
}

bool InitializeMemoryAndRegisters(uint32_t memorySize, uint32_t registerSize)
{
    if (!Flags || !ContainsValueInList(Flags, "notClearMemoryAndRegisters", stringComparer) || !memory || !registers)
    {
        if (memory)
            free(memory);
        if (registers)
            free(registers);

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
    uint8_t *fileContent;
    uint64_t sizeOfFileContent;
#if defined(__WINDOWS__)
    *_exitCode = 1;
    return false;
#elif (defined(__LINUX__) || defined(__APPLE__))
    {
        int file = open(fname, O_RDONLY);
        if (file == -1) {
            *_exitCode = 1;
            return false;
        }

        struct stat buffer;
        int status;
        status = stat(fname, &buffer);
        if (status) {
            *_exitCode = 1;
            return false;
        }

        fileContent = (uint8_t *) mmap(NULL, buffer.st_size, PROT_READ, MAP_PRIVATE, file, 0);

        close(file);

        sizeOfFileContent = buffer.st_size;
    }
#else
    {
        uint64_t fileContentSize = 2;
        uint64_t fileContentUsed = 0;

        fileContent = (uint8_t*)malloc(fileContentSize * sizeof(uint8_t));

        FILE* fptr = fopen(fname, "r");
        if (!fptr)
        {
            *_exitCode = 1;
            return false;
        }

        int c;
        while (true)
        {
            if ((c = fgetc(fptr)) != -1)
            {
                if (fileContentSize <= fileContentUsed + 1)
                {
                    uint8_t* oldFileContent = fileContent;
                    fileContentSize *= 2;
                    fileContent = (uint8_t*)realloc(fileContent, fileContentSize * sizeof(uint8_t));
                    if (!fileContent)
                    {
                        free(oldFileContent);
                        fclose(fptr);
                        *_exitCode = 1;
                        return false;
                    }
                }
                fileContent[fileContentUsed++] = (uint8_t)c;
            }
            else
                break;
        }
        fclose(fptr);
        fileContent[fileContentUsed++] = 0;
        uint8_t* oldFileContent = fileContent;
        fileContent = (uint8_t*)realloc(fileContent, fileContentUsed * sizeof(uint8_t));
        if (!fileContent)
        {
            free(oldFileContent);
            *_exitCode = 1;
            return false;
        }
        sizeOfFileContent = fileContentUsed;
    }
#endif

    uint32_t startPos = 0;
    for (int i = 0; i < sizeOfFileContent - 21; i++)
    {
        if (memcmp((void *) ((uint64_t) fileContent + i), "---End of Metadata---", 21) == 0)
        {
            startPos = i + 21;
            break;
        }
    }

    fileContent += startPos;

    if ((sizeOfFileContent - startPos) % INSTRUCTION_LENGTH != 0)
    {
        *_exitCode = 1;
#if !(defined(__LINUX__) || defined(__APPLE__) || defined(__WINDOWS__))
        free(fileContent);
#endif
        return false;
    }

    if (!InitializeMemoryAndRegisters(4096, 64))
        return false;

    SET_OPCODE_VERSION(1);

    uint32_t numberOfInstructions = (sizeOfFileContent - startPos) / INSTRUCTION_LENGTH;

    for (uint32_t i = 0; i < numberOfInstructions; i++)
    {
        if (!HANDLE_OPCODE((uint8_t *) ((uint64_t) fileContent + i * INSTRUCTION_LENGTH), &i, Memory, Registers))
        {
            *_exitCode = 1;
#if !(defined(__LINUX__) || defined(__APPLE__) || defined(__WINDOWS__))
            free(fileContent);
#endif
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    int exitCode = 0;

    FilesToRun = InitializeList(1);
    Flags = InitializeList(1);

    if (!HandleArgs(--argc, ++argv, FilesToRun, Flags, &exitCode))
        HandleEnd(exitCode);
    for (int i = 0; i < GetSizeFromList(FilesToRun); i++)
    {
        if (!FileExists(GetElementFromList(FilesToRun, i)))
        {
            fprintf(stdout, "File \"%s\" does not exist", GetElementFromList(FilesToRun, i));
            exitCode = 1;
            break;
        }

        if (!HandleFile(GetElementFromList(FilesToRun, i), &exitCode))
            break;
    }

    if (ContainsValueInList(Flags, "printRegisters", stringComparer))
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                printf("%lu ", *(uint64_t*)GetElementFromList(Registers, i * 8 + j));
            printf("\n");
        }
    }

    HandleEnd(exitCode);
}