#include "main.h"

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char* GetFileExtension(char* fileName, size_t len)
{
    if (!fileName) return NULL;
    size_t i;
    for (i = len - 1; i >= 0; i--)
    {
        if (fileName[i] == '.') break;
    }
    if (i == 0) return NULL;
    return &(fileName[i + 1]);
}


int GetCleanLine(FILE* fptr, char** output)
{
    if (*output)
        free(*output);

    int character;
    _Bool nonWhiteSpaceCharacterFound = 0;
    size_t sizeOfOutput = 1;
    size_t usedCharacters = 0;
    *output = (char*)malloc(sizeOfOutput * sizeof(char));
    if (!*output) return -1;
    (*output)[usedCharacters] = '\0';
    while (1)
    {
        character = fgetc(fptr);
        if (character == -1 || character == '\n')
            break;
        if (!nonWhiteSpaceCharacterFound && (character == ' ' || character == '\t'))
            continue;
        nonWhiteSpaceCharacterFound = 1;
        if (usedCharacters + 1 >= sizeOfOutput)
        {
            sizeOfOutput *= 2;
            *output = (char*)realloc(*output, sizeOfOutput * sizeof(char));
            if (!*output) return -1;
        }
        (*output)[usedCharacters] = (char)character;
        (*output)[++usedCharacters] = '\0';
    }

    size_t i = 0;
    for ( ; i < usedCharacters; i++)
    {
        if ((*output)[i] == ';')
        {
            (*output)[i] = '\0';
            usedCharacters = i;
        }
    }

    for (i = usedCharacters - 1; i >= 0; i--)
    {
        if ((*output)[i] != ' ' && (*output)[i] != '\t')
            break;
        (*output)[i] = '\0';
    }

    (*output) = (char*)realloc(*output, (strlen(*output) + 1) * sizeof(char));
    if (!*output) return -1;

    return 0;
}

int SpintString(char* input, char*** output, const char* delimeter, size_t* size)
{
    if (*output)
        free(*output);

    size_t strSize = strlen(input);

    (*size) = 1;
    for (size_t i = 0; i < strSize; i++)
    {
        if (input[i] == delimeter[0])
            (*size)++;
    }

    (*output) = (char**)malloc((*size) * sizeof(char*));
    if (!*output) return -1;
    int pos = 0;
    char* pch = strtok(input, delimeter);
    while (pch != NULL)
    {
        (*output)[pos++] = pch;
        pch = strtok(NULL, delimeter);
    }
    return 0;
}


_Bool mov(char** input, FILE* fptr)
{
    input++;
    //first argument has to be place so must start with $ or m
    if (input[0][0] == '$')
    {
        input[0]++;
        if (input[1][0] == '$')
        {
            fprintf(fptr, "%c%c%c%c%c%c%c%c%c%c%c%c", 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1);
            input[1]++;
            char** eptr = NULL;
            long long r1 = strtoll(input[0], eptr, 10);
            long long r2 = strtoll(input[1], eptr, 10);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&r1)[7 - i], fptr);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&r2)[7 - i], fptr);
        }
        else if (input[1][0] == 'm')
        {
            fprintf(fptr, "%c%c%c%c%c%c%c%c%c%c%c%c", 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2);
            input[1]++;
            char** eptr = NULL;
            long long r1 = strtoll(input[0], eptr, 10);
            long long m2 = strtoll(input[1], eptr, 10);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&r1)[7 - i], fptr);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&m2)[7 - i], fptr);
        }
        else
        {
            fprintf(fptr, "%c%c%c%c%c%c%c%c%c%c%c%c", 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
            char** eptr = NULL;
            long long r1 = strtoll(input[0], eptr, 10);
            long long v2 = strtoll(input[1], eptr, 10);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&r1)[7 - i], fptr);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&v2)[7 - i], fptr);
        }
    }
    else if (input[0][0] == 'm')
    {
        input[0]++;
        if (input[1][0] == '$')
        {
            fprintf(fptr, "%c%c%c%c%c%c%c%c%c%c%c%c", 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 5);
            input[1]++;
            char** eptr = NULL;
            long long m1 = strtoll(input[0], eptr, 10);
            long long r2 = strtoll(input[1], eptr, 10);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&m1)[7 - i], fptr);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&r2)[7 - i], fptr);
        }
        else if (input[1][0] == 'm')
        {
            fprintf(fptr, "%c%c%c%c%c%c%c%c%c%c%c%c", 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 4);
            input[1]++;
            char** eptr = NULL;
            long long m1 = strtoll(input[0], eptr, 10);
            long long m2 = strtoll(input[1], eptr, 10);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&m1)[7 - i], fptr);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&m2)[7 - i], fptr);
        }
        else if (input[1][0] == '"' && input[1][strlen(input[1] - 1)] == '"')
        {
            input[1]++;
            char** eptr = NULL;
            long long m1 = strtoll(input[0], eptr, 10);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&m1)[7 - i], fptr);
            for (int i = 0; i < 8; i++)
                fprintf(fptr, "%c", input[1][strlen(input[1]) - 1 - i]);
        }
        else
        {
            fprintf(fptr, "%c%c%c%c%c%c%c%c%c%c%c%c", 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3);
            char** eptr = NULL;
            long long m1 = strtoll(input[0], eptr, 10);
            long long v2 = strtoll(input[1], eptr, 10);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&m1)[7 - i], fptr);
            for (int i = 0; i < 8; i++)
                fputc(((char*)&v2)[7 - i], fptr);
        }
    }
    else
        return 0;

    for (int i = 0; i < 8; i++)
        fputc(0, fptr);
    return 1;
}

_Bool jmp(char** input, FILE* fptr)
{
    input++;

    fprintf(fptr, "%c%c%c%c", 0, 0, 0, 2);
    char** eptr = NULL;
    unsigned long int val = strtoul(input[0], eptr, 10);
    for (int i = 0; i < 4; i++)
        fputc(((char*)&val)[4 - i], fptr);
    for (int i = 0; i < 28; i++)
        fputc(0, fptr);

    return 1;
}


int main(int argc, char** argv)
{
    argc--;
    argv++;
    if (argc == 1)
    {
        if (strcmp(argv[0], "-h") == 0 || strcmp(argv[0], "--help") == 0)
        {
            fprintf(stdout, "AMPLE Assembler\nSupports AMPLE V1\nExperimental Features\n");
            exit(0);
        }
        else if (strcmp(argv[0], "-v") == 0 || strcmp(argv[0], "--version") == 0)
        {
            fprintf(stdout, "AMPLE Assembler Version: Alpha 0.1\nExperimental Features\n");
            exit(0);
        }
    }

    for (int i = 0; i < argc; i++)
    {
        size_t fileLen = strlen(argv[i]);
        char* fileExt = GetFileExtension(argv[i], fileLen);
        if (fileExt == NULL || fileExt == argv[i])
        {
            fprintf(stderr, "The file \"%s\" caused an unexpected error to happen\n", argv[i]);
            exit(-1);
        }
        if (strcmp(fileExt, "ail") != 0)
        {
            fprintf(stderr, "The file \"%s\" is not of type ample intermediate language\n", argv[i]);
            exit(-1);
        }
        char* destF = (char*)malloc((fileLen + 4) * sizeof(char));
        strcpy(destF, argv[i]);
        snprintf(destF + fileLen - 4, 7, ".ample");

        FILE* src = fopen(argv[i], "r");
        FILE* dest = fopen(destF, "a");

        char* line = NULL;
        char** lArr = NULL;
        size_t arrSize = 0;

        while (!feof(src) && GetCleanLine(src, &line) != -1)
        {
            if (SpintString(line, &lArr, " ", &arrSize) == -1) break;

            if (arrSize == 3 && strcmp(lArr[0], "mov") == 0 && strlen(lArr[1]) != 0 && strlen(lArr[2]) != 0)
            {
                if (!mov(lArr, dest))
                {
                    fprintf(stderr, "Error while assembling file \"%s\"\n", argv[i]);
                }
            }
            else if (arrSize == 2 && strcmp(lArr[0], "jmp") == 0 && strlen(lArr[1]) != 0)
            {
                if (!jmp(lArr, dest))
                {
                    fprintf(stderr, "Error while assembling file \"%s\"\n", argv[i]);
                }
            }

        }

        free(lArr);
        free(line);

        fclose(dest);
        fclose(src);
        free(destF);
    }
}