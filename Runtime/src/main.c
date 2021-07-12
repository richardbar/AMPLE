#include "main.h"

#include <AMPLE.h>

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ArgumentProcessor.h"

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
	 * Make sure to initialize the ArgumentProcessor and output an error message
	 * in case that the ArgumentProcessor does not initialize successfully
	 */
	if (!ArgumentProcessorInitialize()) {
		fprintf(stderr, "Could not initialize the ArgumentProcessor\nRuntime/src/%s:%d\n", __FILENAME__, __LINE__);
		return false;
	}


	return true;
}

void AMPLECleanUp(void) {
	if (HasCleanUp)
		return;

	ArgumentProcessorCleanUp();

	HasCleanUp = true;
}


void AMPLESignalHandler(int sig) {
	AMPLECleanUp();
}


int main(int argc, char** argv) {
	if (!AMPLEInitialize())
		return ExitCode;
}