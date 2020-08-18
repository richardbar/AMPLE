#include "file.h"

#include <stdio.h>

bool FileExists(const char* fname)
{
    FILE* fptr = fopen(fname, "r");
    if (fptr)
    {
        fclose(fptr);
        return true;
    }
    else
        return false;
}