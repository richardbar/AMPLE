#pragma once

#include <AMPLE.h>

#include <stdbool.h>


/**
 * Initialize the Argument Processor
 * @return True if the initialization is successful and false if it fails
 */
bool ArgumentProcessorInitialize();

/**
 * Process arguments passed by arguments
 * @param argNum Number of arguments to process
 * @param argPtr Pointer to arguments
 * @return True if the processing was successful and false if it fails
 */
bool ArgumentProcessorProcessArguments(int argNum, char** argPtr);

/**
 * Gets last exit code of the Argument Processor
 * @return The number of the error, or -1 if the ArgumentProcessor is not initialized
 */
int ArgumentProcessorGetLastErrorCode();

/**
 * Copy the String of the error code. If NULL is passed in str, then
 * the return will contain the number of bytes needed to copy the string
 * @param errorCode Error code
 * @param str Pointer to string, where the string equivalent will be copied
 * @param strSize Numbers of bytes to be copied to the string
 * @return The number of bytes copied, or the number of bytes needed for the error string to be copied if str is NULL, or -1 if the ArgumentProcessor is not initialized
 */
int CopyErrorCodeStr(int errorCode, char* str, int strSize);

/**
 * Clean Up the Argument Processor
 */
void ArgumentProcessorCleanUp();