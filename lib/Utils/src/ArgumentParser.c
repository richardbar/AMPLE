#include "ArgumentParser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "File.h"


typedef struct
{
    const char* name;
    int64_t nameLength;
    const char* value;
    int64_t valueLength;
    uint32_t position;
} ArgumentEntry;

typedef struct
{
    const char* fname;
    int64_t fnameLength;
} FileEntry;

static ArgumentType* argumentTypes = NULL;
static int64_t argumentTypeLength = -1;
static uint32_t argumentTypeIndex = 0;

static ArgumentEntry* argumentEntries = NULL;
static int64_t argumentEntryLength = -1;
static uint32_t argumentEntryIndex = 0;

static FileEntry* fileEntries = NULL;
static int64_t argumentFileEntryLength = -1;
static uint32_t argumentFileEntryIndex = 0;

static bool isArgumentParserInitialized = false;


static bool DoubleArgumentTypesLength()
{
    if (!isArgumentParserInitialized || !argumentTypes || argumentTypeLength <= 0)
        return false;

    int64_t oldArgumentTypeLength = argumentTypeLength;
    argumentTypeLength *= 2;

    ArgumentType* oldPtr = argumentTypes;
    argumentTypes = (ArgumentType*)realloc(argumentTypes, argumentTypeLength * sizeof(ArgumentType));
    if (!argumentTypes)
    {
        argumentTypes = oldPtr;
        argumentTypeLength = oldArgumentTypeLength;
        return false;
    }

    memset(&(argumentTypes[oldArgumentTypeLength]), 0, (argumentTypeLength - oldArgumentTypeLength) * sizeof(ArgumentType));

    return true;
}

static bool DoubleArgumentEntriesLength()
{
    if (!isArgumentParserInitialized || !argumentEntries || argumentEntryLength <= 0)
        return false;

    int64_t oldArgumentEntryLength = argumentEntryLength;
    argumentEntryLength *= 2;

    ArgumentEntry* oldPtr = argumentEntries;
    argumentEntries = (ArgumentEntry*)realloc(argumentEntries, argumentEntryLength * sizeof(ArgumentEntry));
    if (!argumentEntries)
    {
        argumentEntries = oldPtr;
        argumentEntryLength = oldArgumentEntryLength;
        return false;
    }

    memset(&(argumentEntries[oldArgumentEntryLength]), 0, (argumentEntryLength - oldArgumentEntryLength) * sizeof(ArgumentEntry));

    return true;
}

static bool DoubleFileEntriesLength()
{
    if (!isArgumentParserInitialized || !fileEntries || argumentFileEntryLength <= 0)
        return false;

    int64_t oldFileEntryLength = argumentFileEntryLength;
    argumentFileEntryLength *= 2;

    FileEntry* oldPtr = fileEntries;
    fileEntries = (FileEntry*)realloc(fileEntries, argumentFileEntryLength * sizeof(FileEntry));
    if (!fileEntries)
    {
        fileEntries = oldPtr;
        argumentFileEntryLength = oldFileEntryLength;
        return false;
    }

    memset(&(fileEntries[oldFileEntryLength]), 0, (argumentFileEntryLength - oldFileEntryLength) * sizeof(FileEntry));

    return true;
}

static int64_t GetEntryIndex(const char* entryName)
{
    if (!isArgumentParserInitialized || !argumentEntries || !entryName)
        return -1;

    for (uint32_t i = 0; i < argumentEntryLength; i++)
    {
        if (strcmp(argumentEntries[i].name, entryName) == 0)
            return i;
    }

    return -1;
}


bool InitializeArgumentParser()
{
    if (isArgumentParserInitialized)
        return false;

    argumentTypeLength = 1;
    argumentTypes = (ArgumentType*)malloc(argumentTypeLength * sizeof(ArgumentType));
    if (!argumentTypes)
    {
        argumentTypeLength = -1;

        return false;
    }
    memset(argumentTypes, 0, argumentTypeLength * sizeof(ArgumentType));
    argumentTypeIndex = 0;

    argumentEntryLength = 1;
    argumentEntries = (ArgumentEntry*)malloc(argumentEntryLength * sizeof(ArgumentEntry));
    if (!argumentEntries)
    {
        free((void*)argumentTypes);
        argumentTypes = NULL;
        argumentTypeLength = -1;

        argumentEntryLength = -1;

        return false;
    }
    memset(argumentEntries, 0, argumentEntryLength * sizeof(ArgumentEntry));
    argumentEntryIndex = 0;

    argumentFileEntryLength = 1;
    fileEntries = (FileEntry*)malloc(argumentFileEntryLength * sizeof(FileEntry));
    if (!fileEntries)
    {
        free((void*)argumentTypes);
        argumentTypes = NULL;
        argumentTypeLength = -1;

        free((void*)argumentEntries);
        argumentEntries = NULL;
        argumentEntryLength = -1;

        return false;
    }
    memset(fileEntries, 0, argumentFileEntryLength * sizeof(FileEntry));
    argumentFileEntryIndex = 0;

    isArgumentParserInitialized = true;
    return true;
}

bool AddArgumentTypes(ArgumentType* argsType, uint32_t numberOfArgumentTypes)
{
    if (!isArgumentParserInitialized || !argumentTypes || !argsType)
        return false;

    for (uint32_t i = 0; i < numberOfArgumentTypes; i++)
    {
        if (argumentTypeIndex + 1 > argumentTypeLength)
        {
            if (!DoubleArgumentTypesLength())
                return false;
        }

        ArgumentType* temp = (ArgumentType*)malloc(sizeof(ArgumentType));

        if (argsType[i].longType)
        {
            uint32_t longTypeLength = strlen(argsType[i].longType);
            temp->longType = (const char*)malloc((longTypeLength + 1) * sizeof(const char));
            if (!temp->longType)
            {
                free((void*)temp);
                temp = NULL;

                return false;
            }
            memset((char*)(temp->longType), 0, (longTypeLength + 1) * sizeof(const char));
            memcpy((char*)(temp->longType), argsType[i].longType, longTypeLength);
        }

        if (argsType[i].shortType)
        {
            uint32_t shortTypeLength = strlen(argsType[i].shortType);
            temp->shortType = (const char*)malloc((shortTypeLength + 1) * sizeof(const char));
            if (!temp->shortType)
            {
                free((void*)(temp->longType));
                temp->longType = NULL;

                free((void*)temp);
                temp = NULL;

                return false;
            }
            memset((char*)(temp->shortType), 0, (shortTypeLength + 1) * sizeof(const char));
            memcpy((char*)(temp->shortType), argsType[i].shortType, shortTypeLength);
        }

        temp->hasValue = argsType[i].hasValue;
        temp->isOnlyArgument = argsType[i].isOnlyArgument;

        memcpy(&(argumentTypes[argumentTypeIndex++]), temp, sizeof(ArgumentType));

        free(temp);
        temp = NULL;
    }

    return true;
}

bool ParseArguments(char** arguments, uint32_t numberOfArguments, bool silent)
{
    if (numberOfArguments == 0)
    {
        if (!silent)
            fprintf(stderr, "No arguments passed");
        return false;
    }

    bool onlyArgumentFound = false;

    for (uint32_t i = 0; i < numberOfArguments; i++)
    {
        uint32_t sizeOfArgument = strlen(arguments[i]);
        if (sizeOfArgument < 2)
        {
            if (!silent)
                fprintf(stderr, "Argument \"%s\" can not be parsed", arguments[i]);
            return false;
        }

        // Option
        if (arguments[i][0] == '-')
        {
            if (argumentEntryIndex + 1 > argumentEntryLength)
            {
                if (!DoubleArgumentEntriesLength())
                    return false;
            }

            bool found = false;
            // Long Option
            if (arguments[i][1] == '-')
            {
                bool hasValue = false;
                char* argName = &(arguments[i][2]);
                char* argValue = NULL;

                for (uint32_t j = 0; true; j++)
                {
                    if (argName[j] == '\0')
                        break;
                    else if (argName[j] == '=')
                    {
                        hasValue = true;
                        argName[j] = '\0';
                        argValue = &(argName[j + 1]);
                    }
                }

                for (uint32_t j = 0; j < argumentTypeIndex; j++)
                {
                    if (!argumentTypes[j].longType)
                        continue;
                    if (strcmp(argumentTypes[j].longType, argName) == 0)
                    {
                        found = true;

                        ArgumentEntry* temp = (ArgumentEntry*)malloc(sizeof(ArgumentEntry));
                        if (!temp)
                        {
                            return false;
                        }
                        memset(temp, 0, sizeof(ArgumentEntry));

                        temp->nameLength = strlen(argumentTypes[j].longType) + 1;
                        temp->name = (const char*)malloc(temp->nameLength * sizeof(char));
                        if (!temp->name)
                        {
                            free(temp);
                            temp = NULL;

                            return false;
                        }
                        memset((void*)(temp->name), 0, temp->nameLength * sizeof(char));
                        memcpy((char*)(temp->name), (const void*)(argumentTypes[j].longType), temp->nameLength - 1);

                        if (argumentTypes[j].hasValue && hasValue)
                        {
                            temp->valueLength = strlen(argValue) + 1;
                            temp->value = (const char*)malloc(temp->valueLength * sizeof(const char*));
                            if (!temp->value)
                            {
                                free((void*)temp->name);
                                temp->name = NULL;

                                free(temp);
                                temp = NULL;

                                return false;
                            }
                            memset((void*)(temp->value), 0, temp->valueLength * sizeof(char));
                            memcpy((void*)(temp->value), (const void*)(argValue), temp->valueLength - 1);
                        }
                        else
                            temp->valueLength = -1;

                        temp->position = argumentEntryIndex + 1;

                        memcpy(&(argumentEntries[argumentEntryIndex++]), temp, sizeof(ArgumentEntry));

                        free(temp);
                        temp = NULL;

                        if (argumentTypes[j].isOnlyArgument)
                            onlyArgumentFound = true;

                        break;
                    }
                }
            }
            // Short Option
            else
            {
                for (uint32_t j = 0; j < argumentTypeIndex; j++)
                {
                    if (!argumentTypes[j].shortType)
                        continue;
                    if (strcmp(argumentTypes[j].shortType, &(arguments[i][1])) == 0)
                    {
                        found = true;

                        ArgumentEntry* temp = (ArgumentEntry*)malloc(sizeof(ArgumentEntry));
                        if (!temp)
                        {
                            return false;
                        }
                        memset(temp, 0, sizeof(ArgumentEntry));

                        temp->nameLength = strlen(argumentTypes[j].longType) + 1;
                        temp->name = (const char*)malloc(temp->nameLength * sizeof(char));
                        if (!temp->name)
                        {
                            free(temp);
                            temp = NULL;

                            return false;
                        }
                        memset((void*)(temp->name), 0, temp->nameLength * sizeof(char));
                        memcpy((char*)(temp->name), (const void*)(argumentTypes[j].longType), temp->nameLength - 1);

                        temp->valueLength = -1;

                        temp->position = argumentEntryIndex + 1;

                        memcpy(&(argumentEntries[argumentEntryIndex++]), temp, sizeof(ArgumentEntry));

                        free(temp);
                        temp = NULL;

                        if (argumentTypes[j].isOnlyArgument)
                            onlyArgumentFound = true;

                        break;
                    }
                }
            }

            if (!found)
            {
                if (!silent)
                    fprintf(stderr, "Argument \"%s\" is not found\n", arguments[i]);

                return false;
            }
        }
        // Files
        else if (FileExists(arguments[i]))
        {
            if (argumentFileEntryIndex + 1 > argumentFileEntryLength)
            {
                if (!DoubleFileEntriesLength())
                    return false;
            }

            FileEntry* temp = (FileEntry*)malloc(sizeof(FileEntry));
            if (!temp)
            {
                return false;
            }
            memset(temp, 0, sizeof(FileEntry));

            temp->fnameLength = strlen(arguments[i]) + 1;
            temp->fname = (const char*)malloc(temp->fnameLength * sizeof(const char));
            if (!temp->fname)
            {
                free((void*)temp);
                temp = NULL;

                return false;
            }
            memset((void*)(temp->fname), 0, temp->fnameLength * sizeof(char));
            memcpy((char*)(temp->fname), (const void*)(arguments[i]), temp->fnameLength - 1);

            memcpy(&(fileEntries[argumentFileEntryIndex++]), temp, sizeof(FileEntry));

            free((void*)temp);
            temp = NULL;
        }
        // No argument type found or file
        else
        {
            if (!silent)
            {
                fprintf(stderr, "Argument \"%s\" cannot be parsed\n", arguments[i]);
            }
        }
    }

    if (onlyArgumentFound && argumentEntryIndex != 1)
    {
        if (!silent)
            fprintf(stderr, "Some arguments can only exist by themself. Please read documentation\n");

        return false;
    }

    return true;
}

bool ContainsArgument(const char* argument)
{
    if (!isArgumentParserInitialized || !argumentEntries || !argument)
        return false;

    return GetEntryIndex(argument) != -1;
}

uint32_t GetArgumentValueStringLength(const char* argument)
{
    if (!isArgumentParserInitialized || !argumentEntries || !argument)
        return false;

    int64_t index = GetEntryIndex(argument);

    if (index == -1)
        return false;

    return argumentEntries[index].valueLength;
}

bool GetArgumentValueString(const char* argument, char* output, uint32_t size)
{
    if (!isArgumentParserInitialized || !argumentEntries || !argument || !output || size == 0)
        return false;

    int64_t index = GetEntryIndex(argument);

    if (index == -1)
        return false;

    if (argumentEntries[index].valueLength > size)
        return false;

    memcpy(output, argumentEntries[index].value, argumentEntries[index].valueLength);
    return true;
}

bool GetArgumentValueINT64(const char* argument, int64_t* output)
{
    if (!isArgumentParserInitialized || !argumentEntries || !argument || !output)
        return false;

    int64_t index = GetEntryIndex(argument);

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

uint32_t GetNumberOfFiles()
{
    if (!isArgumentParserInitialized || !fileEntries)
        return 0;

    return argumentFileEntryIndex;
}

uint32_t GetFileNameLength(uint32_t position)
{
    if (!isArgumentParserInitialized || !fileEntries || position >= argumentFileEntryIndex)
        return 0;

    return fileEntries[position].fnameLength;
}

bool GetFileName(uint32_t position, char* output, uint32_t size)
{
    if (!isArgumentParserInitialized || !fileEntries || position >= argumentFileEntryIndex || size < fileEntries[position].fnameLength)
        return false;

    memcpy(output, fileEntries[position].fname, fileEntries[position].fnameLength);

    return true;
}

void ClearParsedArguments()
{
    if (!isArgumentParserInitialized || !argumentEntries || !fileEntries)
        return;

    for (uint32_t i = 0; i < argumentEntryIndex; i++)
    {
        ArgumentEntry temp = argumentEntries[i];

        if (temp.name)
        {
            free((void*)(temp.name));
            temp.name = NULL;

            temp.nameLength = -1;
        }

        if (temp.value)
        {
            free((void*)(temp.value));
            temp.value = NULL;

            temp.valueLength = -1;
        }
    }
    free((void*)argumentEntries);
    argumentEntries = NULL;

    for (uint32_t i = 0; i < argumentFileEntryIndex; i++)
    {
        FileEntry temp = fileEntries[i];

        if (temp.fname)
        {
            free((void*)(temp.fname));
            temp.fname = NULL;

            temp.fnameLength = -1;
        }
    }
    free((void*)fileEntries);
    fileEntries = NULL;

    argumentEntryLength = 1;
    argumentEntries = (ArgumentEntry*)malloc(argumentEntryLength * sizeof(ArgumentEntry));
    if (!argumentEntries)
    {
        argumentEntryLength = -1;

        return;
    }
    memset(argumentEntries, 0, argumentEntryLength * sizeof(ArgumentEntry));
    argumentEntryIndex = 0;

    argumentFileEntryLength = 1;
    fileEntries = (FileEntry*)malloc(argumentFileEntryLength * sizeof(FileEntry));
    if (!fileEntries)
    {
        free((void*)argumentEntries);
        argumentEntries = NULL;
        argumentEntryLength = -1;

        argumentFileEntryLength = -1;

        return;
    }
    memset(fileEntries, 0, argumentFileEntryLength * sizeof(FileEntry));
    argumentFileEntryIndex = 0;
}

void CleanupArgumentParser()
{
    if (!isArgumentParserInitialized)
        return;

    if (argumentTypes)
    {
        for (uint32_t i = 0; i < argumentTypeIndex; i++)
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
        for (uint32_t i = 0; i < argumentEntryIndex; i++)
        {
            ArgumentEntry temp = argumentEntries[i];

            if (temp.name)
            {
                free((void*)(temp.name));
                temp.name = NULL;

                temp.nameLength = -1;
            }

            if (temp.value)
            {
                free((void*)(temp.value));
                temp.value = NULL;

                temp.valueLength = -1;
            }
        }

        free((void*)argumentEntries);
        argumentEntries = NULL;
    }
    if (fileEntries)
    {
        for (uint32_t i = 0; i < argumentFileEntryIndex; i++)
        {
            FileEntry temp = fileEntries[i];

            if (temp.fname)
            {
                free((void*)(temp.fname));
                temp.fname = NULL;

                temp.fnameLength = -1;
            }
        }

        free((void*)fileEntries);
        fileEntries = NULL;
    }

    argumentTypeLength = -1;
    argumentTypeIndex = 0;

    argumentEntryLength = -1;
    argumentEntryIndex = 0;

    argumentFileEntryLength = -1;
    argumentFileEntryIndex = 0;

    isArgumentParserInitialized = false;
}