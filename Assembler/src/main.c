#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    fptr = FileOpen("Out.ample", FILE_WRITE | FILE_BINARY);

    if (!fileContent)
    {
        fprintf(stderr, "Could not load file \"%s\"", argv[1]);
        HandleExit(1);
    }

    uint8_t* pch = strtok(fileContent, "\n");
    while (pch != NULL)
    {
        struct Binary* binary = AssembleLine(pch);

        if (binary)
        {
            uint8_t* bytes = (uint8_t*)malloc(32 * sizeof(uint8_t));
            *((int32_t*)bytes) = binary->OpCode;
            *((int32_t*)(bytes + 4)) = binary->Mode;
            *((int64_t*)(bytes + 8)) = binary->Arg1;
            *((int64_t*)(bytes + 16)) = binary->Arg2;
            *((int64_t*)(bytes + 24)) = binary->Arg3;

            fwrite(bytes, 1, 32, fptr);
            fflush(fptr);
        }

        pch = strtok(NULL, "\n");
    }

    free(fileContent);
    FileClose(fptr);
    return 0;
}
