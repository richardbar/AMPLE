#include "main.h"

#include <AMPLE.h>
#include <NFile.h>

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ArgumentProcessor.h"
#include "Execute.h"


/**
 * Allows the Clean up to make sure that it
 * will not clean up everything twice
 */
static bool HasCleanUp = false;


/**
 * AMPLE Exit code. It starts as 1/Error and is set to 0/Success
 * when AMPLE is supposed to exit gracefully.
 */
static int ExitCode = EXIT_FAILURE;


/**
 * All bytes from the program to be opened
 */
static uint8_t* ProgramBytes = NULL;


/**
 * Size of the program loaded
 */
static int64_t ProgramSize = -1;


bool AMPLEInitialize() {
	/**
	 * Makes sure to set the at exit function and outputs an
	 * error message in case that it fails to be set up
	 */
	if (atexit(AMPLECleanUp)) {
		fprintf(stderr, "Could not set up the at exit function\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
		return false;
	}


	/**
	 * Makes sure to set all the signals and outputs an error message
	 * in case that one of those signals fails to be set up
	 */
	#pragma region SetSignals
	if (signal(SIGABRT, AMPLESignalHandler) == SIG_ERR) {
		fprintf(stderr, "Could not set the abort signal\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
		return false;
	}
	if (signal(SIGINT, AMPLESignalHandler) == SIG_ERR) {
		fprintf(stderr, "Could not set the interrupt signal\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
		return false;
	}
	if (signal(SIGFPE, AMPLESignalHandler) == SIG_ERR) {
		fprintf(stderr, "Could not set the floating point error signal\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
		return false;
	}
	if (signal(SIGILL, AMPLESignalHandler) == SIG_ERR) {
		fprintf(stderr, "Could not set the illegal opcode signal\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
		return false;
	}
	if (signal(SIGSEGV, AMPLESignalHandler) == SIG_ERR) {
		fprintf(stderr, "Could not set the segmentation fault signal\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
		return false;
	}
	if (signal(SIGTERM, AMPLESignalHandler) == SIG_ERR) {
		fprintf(stderr, "Could not set the termination signal\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
		return false;
	}
	#pragma endregion


	/**
	 * Make sure to initialize the NFile module from the IO library and output an
	 * error message in case that the NFile module does not initialize successfully
	 */
	if (!NFileInitialize()) {
		fprintf(stderr, "Could not initialize the IO/NFile library\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
		return false;
	}


	/**
	 * Make sure to initialize the ArgumentProcessor and output an error message
	 * in case that the ArgumentProcessor does not initialize successfully
	 */
	if (!ArgumentProcessorInitialize()) {
		fprintf(stderr, "Could not initialize the ArgumentProcessor\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
		return false;
	}


	if (!ExecuteInitialize()) {
		fprintf(stderr, "Could not initialize the Execution module\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
		return false;
	}
	return true;
}


void AMPLECleanUp(void) {
	if (HasCleanUp)
		return;

	NFileCloseAllFiles();
	NFileCleanUp();

	ArgumentProcessorCleanUp();
	ExecuteCleanUp();

	if (ProgramBytes) {
		free(ProgramBytes);
		ProgramBytes = NULL;
	}
	ProgramSize = -1;

	HasCleanUp = true;
}


void AMPLESignalHandler(int sig) {
	/**
	 * Output correct text depending on the signal handled
	 */
	const char* errorText;
	switch (sig) {
		case SIGABRT:
			errorText = "AMPLE abruptly aborted";
			break;
		case SIGINT:
			errorText = "AMPLE abruptly interrupted";
			break;
		case SIGFPE:
			errorText = "AMPLE encountered a floating point exception";
			break;
		case SIGILL:
			errorText = "AMPLE tried to execute an illegal instruction";
			break;
		case SIGSEGV:
			errorText = "AMPLE had a memory segmentation fault";
			break;
		case SIGTERM:
			errorText = "AMPLE abruptly terminated";
			break;
		default:
			errorText = "AMPLE unknown, compile time, signal";
			break;
	}
	fprintf(stderr, "%s\n", errorText);


	/**
	 * Run clean up code, as many systems can not recover
	 */
	AMPLECleanUp();


	/**
	 * Exit AMPLE with the appropriate exit code
	 */
	exit(ExitCode);
}


bool AMPLELoadProgram(char* fname) {
	/**
	 * Check if file exists and if it does not
	 * return false
	 */
	if (!NFileExists(fname)) {
		fprintf(stderr, "File \"%s\" does not exist\n", fname);
		return false;
	}


	/**
	 * Open file given from the command line and check if it can be opened
	 */
	NFILE file = NFileOpen(fname, NFILE_READ | NFILE_BINARY);
	if (!file) {
		fprintf(stderr, "Error opening \"%s\"\n", fname);
		return false;
	}


	/**
	 * Get the file size of the program and if it returns -1/Error
	 * output an error message to the standard error buffer
	 */
	ProgramSize = NFileGetFileSize(file);
	if (ProgramSize == -1) {
		fprintf(stderr, "Error opening \"%s\"\n", fname);
		NFileClose(file);
		return false;
	}


	/**
	 * Allocate memory for the program to load and if it fails
	 * output an error message to the standard error buffer
	 */
	ProgramBytes = (uint8_t*)malloc(ProgramSize);
	if (!ProgramBytes) {
		fprintf(stderr, "Could not load the program into memory\n");
		NFileClose(file);
		return false;
	}


	/**
	 * Read the whole file into memory, check if it failed and
	 * output an error message to the standard error buffer
	 */
	int64_t bytesRead = NFileReadFile(file, ProgramBytes, ProgramSize);
	if (bytesRead != ProgramSize) {
		fprintf(stderr, "Could not load the program into memory successfully\n");
		NFileClose(file);
		return false;
	}


	/**
	 * Close the file after reading everything from it
	 */
	NFileClose(file);

	return true;
}


int main(int argc, char** argv) {
	if (!AMPLEInitialize())
		return ExitCode;

	/**
	 * Process arguments and output the error code in case of an error occurring
	 */
	if (!ArgumentProcessorProcessArguments(argc - 1, &argv[1])) {
		int lastArgumentError = ArgumentProcessorGetLastErrorCode();
		int messageLength = ArgumentProcessorCopyErrorCodeStr(lastArgumentError, NULL, 0);
		char* message = (char*)malloc(messageLength * sizeof(char));
		if (!message) {
			fprintf(stderr, "Error allocating buffer\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
			return ExitCode;
		}
		ArgumentProcessorCopyErrorCodeStr(lastArgumentError, message, messageLength);
		fwrite(message, 1, messageLength, stdout);
		free(message);
		return ExitCode;
	}


	/**
	 * Load program into memory and output
	 * an error message on error
	 */
	char* fname = argv[1];
	if (!AMPLELoadProgram(fname)) {
		fprintf(stderr, "Error loading program file\n");
		return ExitCode;
	}

	ExecuteExecute(ProgramBytes, ProgramSize, 0);

	ExitCode = EXIT_SUCCESS;
	return ExitCode;
}