#include "File.h"

#include "../../../Runtime/include/AMPLE.h"

#if (defined(__LINUX__) || defined(__WINDOWS__) || defined(__APPLE__))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

bool FileExists(const char* fname)
{
#if (defined(__LINUX__) || defined(__WINDOWS__) || defined(__APPLE__))
    FILE* fptr = FileOpen(fname, FILE_READ);
    if (fptr)
    {
        fclose(fptr);
        return true;
    }
    else
        return false;
#else
    return false;
#endif
}

void* FileOpen(const char* fname, uint8_t mode)
{
#if (defined(__LINUX__) || defined(__WINDOWS__) || defined(__APPLE__))
    char fmode[4] = { 0x00, 0x00, 0x00, 0x00 };
    uint8_t bcounter = 1;
    if (mode & FILE_WRITE)
        fmode[0] = 'w';
    else
        fmode[0] = 'r';

    if (mode & FILE_APPEND)
        fmode[bcounter++] = 'a';

    if (mode & FILE_BINARY)
        fmode[bcounter++] = 'b';

    FILE* fptr = fopen(fname, fmode);
    return fptr;
#else
    return NULL;
#endif
}

void FileClose(void* file)
{
    fclose(file);
}

uint32_t FileReadWholeFile(void* file, uint8_t** ptr)
{
    if (!file)
        return 0;

    fseek(file, 0, SEEK_END);
    uint32_t sizeOfFileContent = ftell(file);
    fseek(file, 0, SEEK_SET);

    *ptr = malloc(sizeOfFileContent);
    fread(*ptr, 1, sizeOfFileContent, file);

    return sizeOfFileContent;
}

void GetFileNameWithoutExtension(const char* fname, uint64_t inputSize, char* out)
{
    uint64_t i = inputSize - 1;
    for (; i >= 0; i--)
    {
        if (fname[i] == '.')
            break;
        #if defined(__LINUX__) || defined(__APPLE__)
        if (fname[i] == '/')
        #elif defined(__WINDOWS__)
        if (fname[i] == '\\')
        #endif
            i = 0;
    }

    if (i != 0)
        memccpy(out, fname, 1, i);
}