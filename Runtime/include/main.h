#pragma once

#include <AMPLE.h>

#include <stdbool.h>


#if (defined(__WINDOWS__) || defined(__LINUX__) || defined(__AMPLE__))

/**
 * Main entry point of AMPLE in an OS driven device
 * @param argc Numbers of arguments passed by the command line
 * @param argv Arguments passed by command line
 * @return The exit code
 */
int main(int argc, char** argv);

#else

/**
 * Main entry point of AMPLE in an environment without an OS
 * @return The exit code
 */
void AMPLE();

#endif

/**
 * Initializes All libraries and part of AMPLE and outputs an error if it occurs
 * @return true on success and false on failure
 */
bool AMPLEInitialize();

/**
 * Enters to clean up everything
 */
void AMPLECleanUp(void);

/**
 * Handle signals during execution
 */
void AMPLESignalHandler(int sig);

/**
 * Loads program into memory
 * @param fname File name to load
 * @return true on success and false on failure
 */
bool AMPLELoadProgram(char* fname);