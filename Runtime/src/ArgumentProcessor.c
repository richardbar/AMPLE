#include "ArgumentProcessor.h"

#include <AMPLE.h>
#include <ArgumentParser.h>

#include <stdbool.h>
#include <string.h>


#define __NO_ARGUMENTS_PASSED__ 0x0001
#define __ERROR_ADDING_ARGUMENT_TYPES__ 0x0002
#define __ERROR_PARSING_ARGUMENTS__ 0x0003

static const int StartOfArgumentTypes = __LINE__ + 1;
static ArgumentType ArgumentTypes[] = {
		{
				.longType = "help",
				.shortType = "h",
				.isOnlyArgument = true,
				.hasValue = false
		},
		{
				.longType = "version",
				.shortType = "v",
				.isOnlyArgument = true,
				.hasValue = false
		}
};
static const int EndOfArgumentTypes = __LINE__ - 1;
static int NumberOfArgumentTypes = -1;

static const int StartOfErrorStrings = __LINE__ + 1;
static const char* ErrorStrings[] = {
		"No arguments passed",
		"Error adding argument types to the ArgumentParser library",
		"Error parsing argument types"
};
static const int EndOfErrorStrings = __LINE__ - 1;
static int NumberOfErrorStrings = -1;


/**
 * Boolean to check if ArgumentProcessorInitialize was called
 */
static bool ArgumentProcessorInitialized = false;

/**
 * Int that contains the last error code from an operation
 */
static int ArgumentProcessorErrorCode = -1;


bool ArgumentProcessorInitialize() {
	/**
	 * ArgumentProcessor has already been initialized
	 */
	if (ArgumentProcessorInitialized)
		return true;

	/**
	 * Initialize the ArgumentParser library and return false if it did not initialize
	 */
	if (!ArgumentParserInitialize())
		return false;

	/**
	 * Calculate number of argument types at runtime
	 * sizeof(ArgumentTypes) / sizeof(ArgumentTypes[0]) is not guaranteed to work
	 */
	NumberOfArgumentTypes = (EndOfArgumentTypes - StartOfArgumentTypes - 1) / 6;

	/**
	 * Calculate number of error strings at runtime
	 * sizeof(ErrorStrings) / sizeof(ErrorStrings[0]) is not guaranteed to work
	 */
	NumberOfErrorStrings = (EndOfErrorStrings - StartOfErrorStrings - 1);


	/**
	 * Set ArgumentProcessor Initialized flag to true
	 */
	ArgumentProcessorInitialized = true;

	/**
	 * Return Initialized flag
	 */
	return ArgumentProcessorInitialized;
}


bool ArgumentProcessorProcessArguments(int argNum, char** argPtr) {
	/**
	 *  Check if ArgumentProcessor is initialized
	 */
	if ((!ArgumentProcessorInitialized) ||
			(NumberOfErrorStrings == -1) ||
			(NumberOfArgumentTypes == -1))
		return false;

	/**
	 * Check if no arguments were passed and set error code to appropriate flag
	 */
	if (argNum == 0) {
		ArgumentProcessorErrorCode = __NO_ARGUMENTS_PASSED__;
		return false;
	}

	if (!ArgumentParserAddArgumentTypes(ArgumentTypes, NumberOfArgumentTypes)) {
		ArgumentProcessorErrorCode = __ERROR_ADDING_ARGUMENT_TYPES__;
		return false;
	}

	if (!ArgumentParserParseArguments(argPtr, argNum, false)) {
		ArgumentProcessorErrorCode = __ERROR_PARSING_ARGUMENTS__;
		return false;
	}

	return true;
}


int ArgumentProcessorGetLastErrorCode() {
	return ArgumentProcessorErrorCode;
}

int ArgumentProcessorCopyErrorCodeStr(int errorCode, char* str, int strSize) {
	/**
	 * Check if NumberOfErrorStrings is initialized
	 * Check if ArgumentProcessor is initialized
	 * Check if negative error code passed
	 * Check if error code passed is not included in the ErrorString
	 * Check to see if strSize is non negative if there is a string pointer to be copied
	 * And return -1/Error
	 */
	if ((NumberOfErrorStrings == -1) ||
			(!ArgumentProcessorInitialized) ||
			(errorCode <= 0) ||
			(NumberOfErrorStrings < errorCode) ||
			((str) && (strSize < 0)))
		return -1;

	/**
	 * Get number of bytes needed for the error string to be copied successfully
	 */
	int numberOfBytesNeeded = (int)strlen(ErrorStrings[errorCode - 1]);

	/**
	 * If no string pointer passed to copy string of error code, return number of bytes needed to copy error code string
	 */
	if (!str)
		return numberOfBytesNeeded;

	/**
	 * Calculate number of bytes that can be copied, it can not exceed the min(strSize, numberOfBytesNeeded)
	 */
	int numberOfBytesToBeCopied = (numberOfBytesNeeded > strSize) ? strSize : numberOfBytesNeeded;

	/**
	 * Copy error code string to str
	 */
	memcpy(str, ErrorStrings[errorCode - 1], numberOfBytesToBeCopied * sizeof(char));

	/**
	 * Return the number of characters copied to string
	 */
	return numberOfBytesToBeCopied;
}


void ArgumentProcessorCleanUp() {
	/**
	 * Set Initialized flat to false
	 */
	ArgumentProcessorInitialized = false;

	/**
	 * Clean up ArgumentParser library
	 */
	ArgumentParserCleanup();

	/**
	 * Set other variables to uninitialized state
	 */
	ArgumentProcessorErrorCode = -1;
	NumberOfErrorStrings = -1;
	NumberOfArgumentTypes = -1;
}