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

NFILE fileOpen = NULL;

void HandleInitialization(int argc, char** argv) {
    initialized = false;

    NFileInitialize();

    endian = GetEndianness();
    if (endian == VOODOO_ENDIAN_D) {
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

    initialized = true;
}

void HandleCleanup() {
    if (notClearMemory) {
        free(notClearMemory);
        notClearMemory = NULL;
    }

    if (!printRegisters) {
        free(printRegisters);
        printRegisters = NULL;
    }

    if (!memorySize) {
        free(memorySize);
        memorySize = NULL;
    }

    if (fileOpen) {
        NFileClose(fileOpen);
        fileOpen = NULL;
    }

    NFileCleanUp();

    CleanArguments();
}

void ExitAMPLE() {
    exit(exitCode);
}

bool HandleFile(char* fname) {
    if (!fname || !NFileExists(fname))
        return false;

    fileOpen = NFileOpen(fname, NFILE_READ | NFILE_BINARY);
    if (!fileOpen) {
        fprintf(stderr, "Can not open file \"%s\"\n", fname);
        return false;
    }
    uint64_t fileSize = NFileGetFileSize(fileOpen);
    if (fileSize == -1) {
        fprintf(stderr, "Can not read file \"%s\" properly\n", fname);
        return false;
    }
    uint8_t* fileContent = (uint8_t*)malloc(fileSize * sizeof(uint8_t));
    if (!fileContent) {
        fprintf(stderr, "Can not allocate memory to read program \"%s\"\n", fname);
        return false;
    }
    memset(fileContent, 0x00, fileSize * sizeof(uint8_t));
    uint64_t bytesRead = NFileReadFile(fileOpen, fileContent, fileSize);
    if (bytesRead != fileSize) {
        fprintf(stderr, "Error reading file \"%s\"\n", fname);
        free(fileContent);
        return false;
    }

    printf("%s\n", fileContent);
    free(fileContent);


    NFileClose(fileOpen);
    fileOpen = NULL;

    return true;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        fprintf(stderr, "AMPLE-Runtime needs at least one argument");
        exitCode = -1;
        HandleCleanup();
        ExitAMPLE();
    }

    argc--;
    argv++;

    HandleInitialization(argc, argv);
    if (!initialized) {
        exitCode = -1;
        HandleCleanup();
        ExitAMPLE();
    }

    while (true) {
        char* fname = NULL;
        int32_t fnameSize = GetNextFile(&fname);
        if (fnameSize == -1)
            break;

        if (!HandleFile(fname)) {
            exitCode = 1;
            HandleCleanup();
            ExitAMPLE();
        }
    }


    exitCode = 0;
    HandleCleanup();
    ExitAMPLE();
}