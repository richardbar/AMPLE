#include "file.h"

#include "../../../include/AMPLE.h"

#if (defined(__LINUX__) || defined(__WINDOWS__) || defined(__APPLE__))
#include <stdio.h>
#endif

bool FileExists(const char* fname)
{
#if (defined(__LINUX__) || defined(__WINDOWS__) || defined(__APPLE__))
    FILE* fptr = fopen(fname, "r");
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