#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "File.h"

#include "LineParser.h"

void HandleExit(int _exitCode)
{
    exit(_exitCode);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "You have to provide one file to the Assembler");
        HandleExit(1);
    }

    uint8_t* fileContent = NULL;
    uint32_t fileContentSize;

    FILE* fptr = FileOpen(argv[1], FILE_READ);
    fileContentSize = FileReadWholeFile(fptr, &fileContent);
    FileClose(fptr);

    if (!fileContent)
    {
        fprintf(stderr, "Could not load file \"%s\"", argv[1]);
        HandleExit(1);
    }


    const char* str = " mov r0, r1";
    struct Binary* binary = AssembleLine((uint8_t*)str);

    return 0;
}
