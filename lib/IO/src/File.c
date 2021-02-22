#include "File.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AMPLE.h"

typedef struct
{
    bool initialized;
    char* fname;
    int64_t fnameLength;
    uint8_t mode;
    FILE* fptr;
} FileStruct;


NFILE NFileOpen(const char* fname, uint8_t mode)
{
    if (fname == NULL || mode == 0)
        return NULL;

    char fmode[4] = { 0x00, 0x00, 0x00, 0x00 };
    uint32_t bcounter = 1;

    if (mode & FILE_WRITE)
        fmode[0] = 'w';
    else if (mode & FILE_READ)
        fmode[0] = 'r';
    else
        return NULL;

    if (mode & FILE_APPEND)
        fmode[bcounter++] = 'a';

    if (mode & FILE_BINARY)
        fmode[bcounter] = 'b';

#if defined(__WINDOWS__)
    FILE* fptr = NULL;
    errno_t  errorCode = fopen_s(&fptr, fname, fmode);
    if (errorCode)
        return NULL;
#elif defined(__LINUX__) || defined(__APPLE__)
    FILE* fptr = fopen(fname, fmode);
    if (!fptr)
        return NULL;
#endif

    FileStruct* returnVal = (FileStruct*)malloc(sizeof(FileStruct));
    if (!returnVal)
    {
        fclose(fptr);
        fptr = NULL;
        return NULL;
    }
    memset(returnVal, 0, sizeof(FileStruct));

    returnVal->fnameLength = strlen(fname) + 1;
    returnVal->fname = (char*)malloc(returnVal->fnameLength * sizeof(char));
    if (!returnVal->fname)
    {
        free(returnVal);
        returnVal = NULL;

        fclose(fptr);
        fptr = NULL;

        return NULL;
    }
    memset(returnVal->fname, 0, returnVal->fnameLength * sizeof(char));
    memcpy(returnVal->fname, fname, (returnVal->fnameLength - 1) * sizeof(char));

    returnVal->mode = mode;
    returnVal->fptr = fptr;
    returnVal->initialized = true;


    return (NFILE)returnVal;
}

void NFileClose(NFILE* file)
{
    if (!file)
        return;

    FileStruct* fileStruct = (FileStruct*)file;
    if (!fileStruct->initialized)
        return;

    fileStruct->initialized = false;
    if (fileStruct->fname)
    {
        free(fileStruct->fname);
        fileStruct->fname = NULL;
    }
    fileStruct->fnameLength = 0;

    if (fileStruct->fptr)
    {
        free(fileStruct->fptr);
        fileStruct->fptr = NULL;
    }

    fileStruct->mode = 0;
}

bool NFileExists(const char* fname)
{
    NFILE fptr = NFileOpen(fname, FILE_READ);
    if (fptr)
    {
        NFileClose(&fptr);
        return true;
    }
    else
        return false;
}

int64_t NGetFileSize(NFILE file)
{
    if (!file || !((FileStruct*)file)->initialized || !((FileStruct*)file)->fptr)
        return -1;

    fpos_t pFile;
    fgetpos(((FileStruct*)file)->fptr, &pFile);

    fseek(((FileStruct*)file)->fptr, 0L, SEEK_END);
    int64_t size = ftell(((FileStruct*)file)->fptr);
    fsetpos(((FileStruct*)file)->fptr, &pFile);

    return size;
}

int64_t NReadWholeFile(NFILE file, void* destination, int64_t destionationSize)
{
    if (!file || !((FileStruct*)file)->initialized || !((FileStruct*)file)->fptr)
        return -1;

    int64_t size = NGetFileSize(file);
    if (!destination)
        return size;

    if (destionationSize < size)
        return -1;

    fseek(((FileStruct*)file)->fptr, 0, SEEK_SET);
    return NReadFile(file, destination, size, size);
}

int64_t NReadFile(NFILE file, void* destionation, int64_t destionationSize, int64_t length)
{
    if (!file || !((FileStruct*)file)->initialized || !((FileStruct*)file)->fptr)
        return -1;

    int64_t sizeToBeRead = (length < destionationSize) ? length : destionationSize;
    return fread(destionation, 1, sizeToBeRead, ((FileStruct*)file)->fptr);
}