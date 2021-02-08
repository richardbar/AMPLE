#pragma once

#include <stdbool.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C"
{
#endif

typedef struct {
    const char* longType;
    const char* shortType;
    bool isOnlyArgument;
    bool hasValue;
} ArgumentType;

bool InitializeArgumentParser();

bool AddArgumentTypes(ArgumentType* argumentTypes, uint32_t numberOfArgumentTypes);

bool ParseArguments(char** arguments, uint32_t numberOfArguments, bool silent);

bool ContainsArgument(const char* argument);
uint32_t GetArgumentValueStringLength(const char* argument);
bool GetArgumentValueString(const char* argument, char* output, uint32_t size);
bool GetArgumentValueINT64(const char* argument, int64_t* output);

uint32_t GetNumberOfFiles();
uint32_t GetFileNameLength(uint32_t position);
bool GetFileName(uint32_t position, char* output, uint32_t size);

void ClearParsedArguments();

void CleanupArgumentParser();

#if defined(__cplusplus)
}
#endif