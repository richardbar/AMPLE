#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "BinaryGen.h"
#include "LineParser.h"

static int64_t GetNumber(uint8_t* val)
{
    if (strcmp((const char*)val, "true") == 0)
        return 1;
    else  if (strcmp((const char*)val, "false") == 0)
        return 0;

    int64_t var;
    char c;
    int scanned = sscanf((const char*)val, "%" SCNd64 "%c", &var, &c);
    if (scanned >= 1)
        return var;
    return 0;
}

static bool IsNumber(uint8_t* val)
{
    uint32_t sizeOfVal = strlen((const char*)val);
    if ((strcmp((const char*)val, "true") == 0) || (strcmp((const char*)val, "false") == 0))
        return true;
    if (!sizeOfVal)
        return false;
    for (uint32_t i = 0; i < sizeOfVal; i++)
    {
        if ((val[i] < '0') || ('9' < val[i]))
            return false;
    }

    int64_t var;
    char c;
    int scanned = sscanf((const char*)val, "%" SCNd64 "%c", &var, &c);
    return (scanned >= 1);
}

static bool IsRegister(uint8_t* val)
{
    uint32_t sizeOfVal = strlen((const char*)val);

    return (sizeOfVal > 1 && val[0] == 'r' && IsNumber(val + 1));
}

static bool IsMemory(uint8_t* val)
{
    uint32_t sizeOfVal = strlen((const char*)val);

    return (sizeOfVal > 1 && val[0] == 'm' && IsNumber(val + 1));
}


static bool AppendArgument(struct Instruction* instruction, struct Argument* argument)
{
    if (!instruction->numberOfArguments)
    {
        instruction->arguments = (struct Argument*)malloc(sizeof(struct Argument));
        if (!instruction->arguments)
            return false;
    }
    else
    {
        instruction->arguments = (struct Argument*)realloc(instruction->arguments, (instruction->numberOfArguments + 1) * sizeof(struct Argument));
        if (!instruction->arguments)
            return false;
    }

    memcpy(&(instruction->arguments[instruction->numberOfArguments++]), argument, sizeof(struct Argument));

    return true;
}



struct Argument* InitializeArgument(uint8_t* val)
{
    struct Argument* argument = (struct Argument*)malloc(sizeof(struct Argument));
    if (!argument)
        return NULL;

    uint32_t sizeOfVal = strlen((const char*)val);
    argument->str = (uint8_t*)malloc((sizeOfVal + 1) * sizeof(uint8_t));
    if (!argument->str)
    {
        free(argument);
        return NULL;
    }
    memcpy(argument->str, val, sizeOfVal + 1);

    if (IsRegister(val))
    {
        argument->type = REGISTER;
        val++;
    }
    else if (IsMemory(val))
    {
        argument->type = MEMORY;
        val++;
    }
    else if (IsNumber(val))
        argument->type = NUMBER;
    else
        return NULL;

    argument->value = GetNumber(val);

    return argument;
}

void FreeArgument(struct Argument* argument)
{
    free(argument->str);
    free(argument);
}



struct Instruction* InitializeInstruction(uint8_t* mnemonic)
{
    struct Instruction* instruction = (struct Instruction*)malloc(sizeof(struct Instruction));
    if (!instruction)
        return NULL;

    uint32_t sizeOfMnemonic = strlen((const char*)mnemonic);
    instruction->mnemonic = (uint8_t*)malloc((sizeOfMnemonic + 1) * sizeof(char));
    if (!instruction->mnemonic)
    {
        free(instruction);
        return NULL;
    }
    memcpy(instruction->mnemonic, mnemonic , sizeOfMnemonic + 1);

    instruction->arguments = NULL;
    instruction->numberOfArguments = 0;

    instruction->AppendArgument = AppendArgument;

    return instruction;
}

void FreeInstruction(struct Instruction* instruction)
{
    free(instruction->mnemonic);
    free(instruction->arguments);
    free(instruction);
}


struct Binary* AssembleLine(uint8_t* line)
{
    uint32_t lineLength = strlen((const char*)line);
    uint32_t sizeOfMnemonic = 0;

    // Clean whitespaces before actual line begins
    for (uint32_t i = 0; i < lineLength; i++)
    {
        if (line[i] == ' ' || line[i] == '\t')
        {
            line++;
            lineLength--;
        }
        else
            break;
    }

    // Clears comments from end of line
    for (uint64_t i = 0; i < lineLength; i++)
    {
        if (line[i] == '#')
        {
            lineLength = i;
            line[i] = '\0';
            break;
        }
    }
    lineLength = strlen((const char*)line);

    // Find end of mnemonic
    for (uint32_t i = 0; i < lineLength; i++)
    {
        if (line[i] == ' ' || line[i] == '\t')
        {
            sizeOfMnemonic = i;
            break;
        }
    }

    // Flag
    if (line[0] == '.')
    {

        return NULL;
    }
    else
    {
        line[sizeOfMnemonic] = '\0';
        struct Instruction* instruction = InitializeInstruction(line);
        if (!instruction)
            return false;
        line += sizeOfMnemonic + 1;
        sizeOfMnemonic = strlen((const char*)line);

        int64_t startOfArgument = -1;
        int64_t endOfArgument = -1;
        for (int32_t i = 0; i < sizeOfMnemonic; i++)
        {
            if ((startOfArgument == -1) && ((line[i] != ' ') && (line[i] != '\t')))
                startOfArgument = i;
            if (((startOfArgument != -1) && (endOfArgument == -1) && (line[i] == ',')) || i + 1 == sizeOfMnemonic)
            {
                endOfArgument = i;
                if (i + 1 == sizeOfMnemonic)
                    endOfArgument++;
            }

            if ((startOfArgument != -1) && (endOfArgument != -1))
            {
                uint32_t sizeOfArgument = endOfArgument - startOfArgument;
                uint8_t* argumentStr = (uint8_t*)malloc((sizeOfArgument + 1)* sizeof(uint8_t));
                uint8_t* initialArgumentStr = argumentStr;
                if (!argumentStr)
                    return NULL;

                memcpy(argumentStr, &(line[startOfArgument]), sizeOfArgument);
                argumentStr[sizeOfArgument] = '\0';

                for (uint32_t j = 0; j < sizeOfArgument; j++)
                {
                    if ((argumentStr[j] != ' ') && (argumentStr[j] != '\t'))
                    {
                        argumentStr += j;
                        sizeOfArgument -= j;
                        break;
                    }
                }
                for (int64_t j = sizeOfArgument - 1; j >= 0; j--)
                {
                    if ((argumentStr[j] == ' ') || (argumentStr[j] == '\t'))
                        argumentStr[j] = '\0';
                }

                struct Argument* arg = InitializeArgument(argumentStr);
                if (!arg)
                {
                    free(initialArgumentStr);
                    return NULL;
                }

                instruction->AppendArgument(instruction, arg);

                free(initialArgumentStr);
                startOfArgument = -1;
                endOfArgument = -1;
            }
        }



        struct Binary* binary = (struct Binary*)malloc(sizeof(struct Binary));
        if (!binary)
            return NULL;

        if (!Generate(instruction, binary))
        {
            free(binary);
            free(instruction);
            return NULL;
        }

        free(instruction);
        return binary;
    }
}