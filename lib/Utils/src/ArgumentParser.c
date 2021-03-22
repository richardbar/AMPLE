#include "ArgumentParser.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AMPLE.h"
#include "File.h"


#define PRINT_IF_NOT_SILENT(stream, ...)        \
    if (!silent)                                \
        fprintf(stream, __VA_ARGS__)


typedef struct
{
    const char* name;
    uint64_t nameLength;
    const char* value;
    uint64_t valueLength;
    uint64_t position;
} ArgumentEntry;

typedef struct
{
    const char* fname;
    uint64_t position;
} FileEntry;


ArgumentType* argumentTypes = NULL;
int64_t argumentTypeCount = -1;
int64_t argumentTypeSize = 0;

ArgumentEntry* argumentEntries = NULL;
int64_t argumentEntryCount = -1;
int64_t argumentEntrySize = 0;

FileEntry* fileEntries = NULL;
int64_t fileEntryCount = -1;
int64_t fileEntrySize = 0;

bool isArgumentParserInitialized = false;


/**
 * Doubles the length of the arugmentTypes array and zeroes the new entries
 * @return true upon success and false upon failure
 */
bool ArgumentParserDoubleArgumentTypesLength() {
    if (!argumentTypes || argumentTypeCount == -1 || !isArgumentParserInitialized)
        return false;

    uint64_t newArgumentTypeCount = argumentTypeCount * 2;
    if (newArgumentTypeCount < argumentTypeCount)               // Overflow
        return false;

    ArgumentType* newArgumentTypes = (ArgumentType*)realloc(argumentTypes, newArgumentTypeCount * sizeof(ArgumentType));
    if (!newArgumentTypes)                                      // Out of memory
        return false;

    memset(&(newArgumentTypes[argumentTypeCount]), 0x00, argumentTypeCount * sizeof(ArgumentType));

    argumentTypes = newArgumentTypes;
    argumentTypeCount = newArgumentTypeCount;

    return true;
}

/**
 * Doubles the length of the arugmentEntries array and zeroes the new entries
 * @return true upon success and false upon failure
 */
bool ArgumentParserDoubleArgumentEntriesLength() {
    if (!argumentEntries || argumentEntryCount == -1 || !isArgumentParserInitialized)
        return false;

    uint64_t newArgumentEntryCount = argumentEntryCount * 2;
    if (newArgumentEntryCount < argumentEntryCount)             // Overflow
        return false;

    ArgumentEntry* newArgumentEntries = (ArgumentEntry*)realloc(argumentEntries, newArgumentEntryCount * sizeof(ArgumentEntry));
    if (!newArgumentEntries)                                    // Out of memory
        return false;

    memset(&(newArgumentEntries[argumentEntryCount]), 0x00, argumentEntryCount * sizeof(ArgumentEntry));

    argumentEntries = newArgumentEntries;
    argumentEntryCount = newArgumentEntryCount;

    return true;
}

/**
 * Doubles the length of the fileEntries array and zeroes the new entries
 * @return true upon success and false upon failure
 */
bool ArgumentParserDoubleFileEntriesLength() {
    if (!fileEntries || fileEntryCount == -1 || !isArgumentParserInitialized)
        return false;

    uint64_t newFileEntryCount = fileEntryCount * 2;
    if (newFileEntryCount < fileEntryCount)                     // Overflow
        return false;

    FileEntry* newFileEntries = (FileEntry*)realloc(fileEntries, newFileEntryCount * sizeof(FileEntry));
    if (!newFileEntries)                                        // Out of memory
        return false;

    memset(&(newFileEntries[fileEntryCount]), 0x00, fileEntryCount * sizeof(FileEntry));

    fileEntries = newFileEntries;
    fileEntryCount = newFileEntryCount;

    return true;
}


/**
 * Finds the index of an argument entry after parsing
 * Also can be used to check if an argument was passed or not
 * @param entryName C String of the argument entry to check if exists
 * @return non negative int of index if found or -1 in case it is not found
 */
INLINE int64_t ArgumentParserGetEntryIndex(const char* entryName) {
    if (!isArgumentParserInitialized || !argumentEntries || !entryName)
        return -1;

    for (int64_t i = 0; i < argumentEntryCount; i++) {
        if (!argumentEntries[i].name)
            continue;

        if (strcmp(argumentEntries[i].name, entryName) == 0)
            return i;
    }

    return -1;
}


/**
 * Creates a FileEntry struct and adds it to the fileEntries array
 * @param fname Name of the file
 * @param position Position in the arguments passed to parse
 * @return true upon success and false upon failure
 */
bool INLINE ArgumentParserInsertFileEntry(const char* fname, uint64_t position) {
    if (!isArgumentParserInitialized || !fileEntries || !fname || fileEntryCount == -1 || !NFileExists(fname))
        return false;

    if (fileEntrySize >= fileEntryCount) {
        if (!ArgumentParserDoubleFileEntriesLength())
            return false;
    }

    FileEntry* thisEntry = &(fileEntries[fileEntrySize]);

    uint64_t fnameLength = strlen(fname);

    thisEntry->fname = (const char*)malloc((fnameLength + 1) * sizeof(const char));
    if (!thisEntry->fname)
        return false;
    memcpy((char*)thisEntry->fname, fname, (fnameLength + 1) * sizeof(const char));

    thisEntry->position = position;

    fileEntrySize++;

    return true;
}


bool ArgumentParserInitialize() {
    if (isArgumentParserInitialized || argumentTypeCount != -1 || argumentEntryCount != -1 || fileEntryCount != -1)
        return false;

    argumentTypeCount = 1;
    argumentTypes = (ArgumentType*)malloc(argumentTypeCount * sizeof(ArgumentType));
    if (!argumentTypes) {
        argumentTypeCount = -1;
        return false;
    }
    memset(argumentTypes, 0x00, argumentTypeCount * sizeof(ArgumentType));
    argumentTypeSize = 0;

    argumentEntryCount = 1;
    argumentEntries = (ArgumentEntry*)malloc(argumentEntryCount * sizeof(ArgumentEntry));
    if (!argumentEntries) {
        free((void*)argumentTypes);
        argumentTypes = NULL;
        argumentTypeCount = -1;

        argumentEntryCount = -1;
        return false;
    }
    memset(argumentEntries, 0, argumentEntryCount * sizeof(ArgumentEntry));
    argumentEntrySize = 0;

    fileEntryCount = 1;
    fileEntries = (FileEntry*)malloc(fileEntryCount * sizeof(FileEntry));
    if (!fileEntries) {
        free((void*)argumentTypes);
        argumentTypes = NULL;
        argumentTypeCount = -1;

        free((void*)argumentEntries);
        argumentEntries = NULL;
        argumentEntryCount = -1;

        fileEntryCount = -1;
        return false;
    }
    memset(fileEntries, 0, fileEntryCount * sizeof(FileEntry));
    fileEntrySize = 0;

    isArgumentParserInitialized = true;
    return true;
}


bool ArgumentParserAddArgumentType(ArgumentType* argType) {
    if (!isArgumentParserInitialized || !argumentTypes || !argType || argumentTypeCount == -1)
        return false;

    if (argumentTypeSize >= argumentTypeCount) {
        if (!ArgumentParserDoubleArgumentTypesLength())
            return false;
    }

    ArgumentType* thisType = &(argumentTypes[argumentTypeSize]);

    if (argType->longType) {
        uint64_t longTypeLength = strlen(argType->longType);

        thisType->longType = (const char*)malloc((longTypeLength + 1) * sizeof(const char));
        if (!thisType->longType)
            return false;
        memcpy((char*)thisType->longType, argType->longType, (longTypeLength + 1) * sizeof(const char));
    }

    if (argType->shortType) {
        uint64_t shortTypeLength = strlen(argType->shortType);

        thisType->shortType = (const char*)malloc((shortTypeLength + 1) * sizeof(const char));
        if (!thisType->shortType) {
            if (thisType->longType) {
                free((void*)thisType->longType);
                thisType->longType = NULL;
            }
            return false;
        }
        memcpy((char*)thisType->shortType, argType->shortType, (shortTypeLength + 1) * sizeof(const char));
    }

    thisType->hasValue = argType->hasValue;
    thisType->isOnlyArgument = argType->isOnlyArgument;

    argumentTypeSize++;

    return true;
}

bool ArgumentParserAddArgumentTypes(ArgumentType* argsType, int64_t numberOfArgumentTypes) {
    if (!isArgumentParserInitialized || !argumentTypes || !argsType || numberOfArgumentTypes < 0 || argumentTypeCount == -1)
        return false;

    for (int64_t i = 0; i < numberOfArgumentTypes; i++) {
        if (!ArgumentParserAddArgumentType(&(argsType[i])))
            return false;
    }

    return true;
}


bool ArgumentParserParseArguments(char** arguments, uint64_t numberOfArguments, bool silent) {
    if (!isArgumentParserInitialized || !argumentTypes || !arguments || !argumentEntries || argumentEntryCount == -1 || !fileEntries || fileEntryCount == -1 || argumentTypeCount == -1) {
        PRINT_IF_NOT_SILENT(stderr, "AMPLE Argument Parser: AMPLE Argument Parser has not been initialized\n");
        return false;
    }

    if (numberOfArguments == 0) {
        PRINT_IF_NOT_SILENT(stderr, "AMPLE Argument Parser: No arguments were parsed\n");
        return false;
    }

    bool onlyArgumentFound = false;

    for (uint64_t i = 0; i < numberOfArguments; i++) {
        uint64_t sizeOfArgument = strlen(arguments[i]);
        if (sizeOfArgument < 2) {
            PRINT_IF_NOT_SILENT(stderr, "AMPLE Argument Parser: Can not parse \"%s\". Too short\n", arguments[i]);
            return false;
        }

        // Option detected
        if (arguments[i][0] == '-') {
            if (argumentEntrySize >= argumentEntryCount) {
                if (!ArgumentParserDoubleArgumentEntriesLength()) {
                    PRINT_IF_NOT_SILENT(stderr, "AMPLE Argument Parser: Can not extend the argumentEntry array\n");
                    return false;
                }
            }
            ArgumentEntry* thisEntry = &(argumentEntries[argumentEntrySize]);

            // Long Option
            if (arguments[i][1] == '-') {
                int64_t argumentLength = strlen(&(arguments[i][2]));
                for (int64_t j = 0; j < argumentTypeSize; j++) {
                    if (!argumentTypes[j].longType)
                        continue;

                    int64_t longTypeLength = strlen(argumentTypes[j].longType);
                    if (longTypeLength > argumentLength)
                        continue;
                    if (memcmp(argumentTypes[j].longType, &(arguments[i][2]), longTypeLength) == 0) {
                        if (argumentTypes[j].isOnlyArgument)
                            onlyArgumentFound = true;

                        thisEntry->name = argumentTypes[j].longType;
                        thisEntry->nameLength = strlen(argumentTypes[j].longType);
                        thisEntry->position = i;
                        if (!argumentTypes[j].hasValue) {
                            thisEntry->value = NULL;
                            thisEntry->valueLength = 0;
                        }
                        else {
                            bool hasValue = false;
                            char* argValue = NULL;

                            for (int64_t k = 2; true; k++) {
                                if (arguments[i][k] == '\0')
                                    break;
                                else if (arguments[i][k] == '=') {
                                    hasValue = true;
                                    argValue = &(arguments[i][k + 1]);
                                    break;
                                }
                            }

                            if (!hasValue) {
                                thisEntry->value = NULL;
                                thisEntry->valueLength = 0;
                            }
                            else {
                                thisEntry->valueLength = strlen(argValue);
                                thisEntry->value = (const char*)malloc((thisEntry->valueLength + 1) * sizeof(const char));
                                if (!thisEntry->value) {
                                    PRINT_IF_NOT_SILENT(stderr, "AMPLE Argument Parser: Can not save value of \"%s\n", &(arguments[i][2]));
                                    return false;
                                }
                                memcpy((char*)thisEntry->value, argValue, (thisEntry->valueLength + 1) * sizeof(const char));
                            }
                        }

                        break;
                    }
                }
            }
            // Short Option
            else {
                for (int64_t j = 0; j < argumentTypeSize; j++) {
                    if (!argumentTypes[j].shortType)                // Current type doesn't support a short type
                        continue;

                    if (strcmp(argumentTypes[j].shortType, &(arguments[i][1])) == 0) {
                        if (argumentTypes[j].isOnlyArgument)
                            onlyArgumentFound = true;

                        thisEntry->name = argumentTypes[j].shortType;
                        thisEntry->nameLength = strlen(argumentTypes[j].shortType);
                        thisEntry->position = i;
                        thisEntry->value = NULL;
                        thisEntry->valueLength = 0;

                        break;
                    }
                }
            }

            argumentEntrySize++;
        }
        // File detected
        else if (NFileExists(arguments[i])) {
            if (!ArgumentParserInsertFileEntry(arguments[i], i)) {
                PRINT_IF_NOT_SILENT(stderr, "AMPLE Argument Parser: Can not insert file \"%s\" in the fileEntries array", arguments[i]);
                return false;
            }
        }
        // Fail
        else {
            PRINT_IF_NOT_SILENT(stderr, "AMPLE Argument Parser: Can not parse \"%s\". Not an option nor a file", arguments[i]);
            return false;
        }
    }

    if (onlyArgumentFound && (numberOfArguments > 1)) {
        PRINT_IF_NOT_SILENT(stderr, "AMPLE Argument Parser: Some arguments can only exist by themself. Please read documentation\n");
        return false;
    }

    return true;
}


bool ArgumentParserContainsArgument(const char* argument)
{
    if (!isArgumentParserInitialized || !argumentEntries || argumentEntryCount == -1 || !argument)
        return false;

    return ArgumentParserGetEntryIndex(argument) != -1;
}

int64_t ArgumentParserGetArgumentValueStringLength(const char* argument)
{
    if (!isArgumentParserInitialized || !argumentEntries || argumentEntryCount == -1 || !argument)
        return false;

    int64_t index = ArgumentParserGetEntryIndex(argument);

    if (index == -1)
        return -1;

    return argumentEntries[index].valueLength;
}

bool ArgumentParserGetArgumentValueString(const char* argument, char* output, uint32_t size)
{
    if (!isArgumentParserInitialized || !argumentEntries || argumentEntryCount == -1 || !argument || !output || size == 0)
        return false;

    int64_t index = ArgumentParserGetEntryIndex(argument);

    if (index == -1)
        return false;

    if (argumentEntries[index].valueLength > size)
        return false;

    memcpy(output, argumentEntries[index].value, argumentEntries[index].valueLength);
    return true;
}

bool ArgumentParserGetArgumentValueINT64(const char* argument, int64_t* output)
{
    if (!isArgumentParserInitialized || !argumentEntries || argumentEntryCount == -1 || !argument || !output)
        return false;

    int64_t index = ArgumentParserGetEntryIndex(argument);

    if (index == -1)
        return false;

    if (argumentEntries[index].valueLength == 0)
        return false;

    int base = 10;
    if (argumentEntries[index].value[0] == '0')
    {
        if (argumentEntries[index].valueLength > 2)
        {
            if (argumentEntries[index].value[1] == 'x')
                base = 16;
            if (argumentEntries[index].value[1] == 'b')
                base = 2;
        }
    }
    *output = strtoll(argumentEntries[index].value, NULL, base);
    return true;
}

int64_t ArgumentParserGetNumberOfFiles()
{
    if (!isArgumentParserInitialized || !fileEntries || fileEntryCount == -1)
        return 0;

    return fileEntrySize;
}

int64_t ArgumentParserGetFileNameLength(int64_t position)
{
    if (!isArgumentParserInitialized || !fileEntries || fileEntryCount == -1 || position < 0 || position >= fileEntryCount || !fileEntries[position].fname)
        return -1;

    return strlen(fileEntries[position].fname);
}

bool ArgumentParserGetFileName(int64_t position, char* output, int64_t size)
{
    if (!isArgumentParserInitialized || !fileEntries || fileEntryCount == -1 || position < 0 || position >= fileEntrySize || !fileEntries[position].fname || size < strlen(fileEntries[position].fname))
        return false;

    memcpy(output, fileEntries[position].fname, strlen(fileEntries[position].fname));

    return true;
}

void ArgumentParserCleanup()
{
    if (!isArgumentParserInitialized)
        return;

    if (argumentTypes)
    {
        for (int64_t i = 0; i < argumentTypeSize; i++)
        {
            ArgumentType temp = argumentTypes[i];

            if (temp.longType)
            {
                free((void*)(temp.longType));
                temp.longType = NULL;
            }

            if (temp.shortType)
            {
                free((void*)(temp.shortType));
                temp.shortType = NULL;
            }
        }

        free((void*)argumentTypes);
        argumentTypes = NULL;
    }
    if (argumentEntries)
    {
        for (int64_t i = 0; i < argumentEntrySize; i++)
        {
            ArgumentEntry* temp = &(argumentEntries[i]);

            if (temp->name)
            {
                // Already freed by argument types
                temp->name = NULL;
                temp->nameLength = -1;
            }

            if (temp->value)
            {
                free((void*)(temp->value));
                temp->value = NULL;

                temp->valueLength = -1;
            }
        }

        free((void*)argumentEntries);
        argumentEntries = NULL;
    }
    if (fileEntries)
    {
        for (int64_t i = 0; i < fileEntrySize; i++)
        {
            FileEntry* temp = &(fileEntries[i]);

            if (temp->fname)
            {
                free((void*)(temp->fname));
                temp->fname = NULL;
            }
        }

        free((void*)fileEntries);
        fileEntries = NULL;
    }

    argumentTypeCount = -1;
    argumentTypeSize = 0;

    argumentEntryCount = -1;
    argumentEntrySize = 0;

    fileEntryCount = -1;
    fileEntrySize = 0;

    isArgumentParserInitialized = false;
}