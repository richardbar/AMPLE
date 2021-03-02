#include "AMPLE.h"

#include "File.h"

#include <stdint.h>
#if defined(__GNUC__)
    #define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AMPLE.h"

#if defined(__WINDOWS__)
    #include <windows.h>
#endif

typedef struct
{
    int64_t uniqueID;
    char* fname;
    int64_t fnameLength;
    uint8_t mode;
    bool open;
    FILE* fptr;
    uint64_t position;
} FileStruct;

FileStruct* openFiles = NULL;
uint64_t openFilesCount = 0;
uint64_t openFilesSize = 0;

int64_t currentUniqueID = 3;

static bool InitializeNFile()
{
    openFilesCount = 1;
    openFiles = (FileStruct*)malloc(openFilesCount * sizeof(FileStruct));
    if (!openFiles)
    {
        openFilesCount = 0;
        return false;
    }

    return true;
}

static bool doubleOpenFiles()
{
    if (!openFiles && !InitializeNFile())
        return false;

    openFilesCount *= 2;
    FileStruct* temp = (FileStruct*)realloc(openFiles, openFilesCount * sizeof(FileStruct));
    if (!temp)
    {
        openFilesCount /= 2;
        return false;
    }
    openFiles = temp;
    return true;
}


NFILE NFileOpen(const char* fname, uint8_t mode)
{
    if ((!openFiles && !InitializeNFile()) || ((openFilesSize + 1 > openFilesCount) && !doubleOpenFiles()))
        return -1;

    char fmode[4] = { 0x00, 0x00, 0x00, 0x00 };
    uint8_t bcounter = 0;
    if (mode & FILE_WRITE)
        fmode[bcounter++] = 'w';
    else if (mode & FILE_READ)
        fmode[bcounter++] = 'r';
    else
        fmode[bcounter++] = 0x00;

    if (mode & FILE_APPEND)
        fmode[bcounter++] = 'a';
    if (mode & FILE_BINARY)
        fmode[bcounter] = 'b';

    FILE* fptr;
#if defined(__WINDOWS__)
    errno_t errorCode = fopen_s(&fptr, fname, fmode);
    if (errorCode)
        return -1;
#elif defined(__LINUX__) || defined(__APPLE__)
    fptr = fopen(fname, fmode);
    if (!fptr)
        return -1;
#endif

    FileStruct temp = openFiles[openFilesSize++];

    temp.uniqueID += currentUniqueID++;

    temp.fnameLength = strlen(fname) + 1;
    temp.fname = (char*)malloc(temp.fnameLength * sizeof(char));
    if (!temp.fname)
    {
        currentUniqueID--;
        openFilesSize--;
        return -1;
    }
    memcpy(temp.fname, fname, temp.fnameLength);
    temp.fname[temp.fnameLength] = 0;

    temp.mode = mode;

    temp.open = true;

    temp.fptr = fptr;

    temp.position = 0;

    return temp.uniqueID;
}

void NFileClose(NFILE* file)
{
}

bool NFileExists(const char* fname)
{
    FILE* fptr;
#if defined(__WINDOWS__)
    errno_t errorCode = fopen_s(&fptr, fname, "r");
    if (errorCode)
        return false;
#elif defined(__LINUX__) || defined(__APPLE__)
    fptr = fopen(fname, "r");
    if (!fptr)
        return false;
#endif
    fclose(fptr);
    return true;
}

int64_t NGetFileSize(NFILE file)
{
}

int64_t NReadWholeFile(NFILE file, void* destination, int64_t destionationSize)
{
}

int64_t NReadFile(NFILE file, void* destionation, int64_t destionationSize, int64_t length)
{
}

void FCloseAllFiles()
{
#if defined(__WINDOWS__)
    _fcloseall();
#elif defined(__GNUC__)
#endif
}