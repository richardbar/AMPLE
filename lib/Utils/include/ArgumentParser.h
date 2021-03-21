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


/**
 * Initialize the Argument Parser library
 * @return True upon success and false upon failure
 */
bool ArgumentParserInitialize();


/**
 * Adds new Argument Type to the Argument Parser Library
 * @param argsType Arugment Type to add
 * @return True upon success and false upon failure
 */
bool ArgumentParserAddArgumentType(ArgumentType* argType);

/**
 * Adds new Argument Types to the Argument Parser Library
 * @param argumentTypes Arugment Type array to add
 * @param numberOfArgumentTypes Length of the Argument Type array
 * @return True upon success and false upon failure
 */
bool ArgumentParserAddArgumentTypes(ArgumentType* argumentTypes, int64_t numberOfArgumentTypes);


/**
 * Parse arguments given by the int main(int argc, char** argv) function
 * @param arguments Array of C style strings
 * @param numberOfArguments Number of C styled strings in array
 * @param silent True if no error output to be printed in stderr
 * @return True upon success and false upon failure
 */
bool ArgumentParserParseArguments(char** arguments, uint64_t numberOfArguments, bool silent);


/**
 * Checks if an argument is contained
 * @param argument String long type check
 * @return True if it exists and false if not
 */
bool ArgumentParserContainsArgument(const char* argument);

/**
 * Get the number of bytes the value of the the argument has
 * @param argument String long type
 * @return A positive number for the bytes, 0 if there was no value and -1 if the argument does not exist
 */
int64_t ArgumentParserGetArgumentValueStringLength(const char* argument);

/**
 * Get the value of an argument passed
 * @param argument String long type
 * @param output String output
 * @param size Size the output
 * @return True if the copying was successful and false if not
 */
bool ArgumentParserGetArgumentValueString(const char* argument, char* output, uint32_t size);

/**
 * Get the value of an argument passed as an int64
 * @param argument String long type
 * @param output int64 output
 * @return True if the copying was successful and false if not
 */
bool ArgumentParserGetArgumentValueINT64(const char* argument, int64_t* output);

/**
 * Get the number of files parsed with the Argument Parser
 * @return The number of files parsed on success or -1 on failure
 */
int64_t ArgumentParserGetNumberOfFiles();

/**
 * Get the number of bytes of how long is the next file
 * @param position Index of the file
 * @return Thr number of bytes of the file name
 */
int64_t ArgumentParserGetFileNameLength(int64_t position);

/**
 * Copy filename of the given index to output
 * @param position Index of the file
 * @param output Output variable
 * @param size Number of bytes that has the output
 * @return True upon success and fale upon failure
 */
bool ArgumentParserGetFileName(int64_t position, char* output, int64_t size);


/**
 * Clean up and de initialize the Argument Parse library
 */
void ArgumentParserCleanup();


#if defined(__cplusplus)
}
#endif