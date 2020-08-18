#pragma once

#include <stdbool.h>

#include "List.h"

/**
 * @param argNum argNum Number of arguments to be parsed
 * @param argPtr Pointer to array of string pointers to be parsed
 * @param filesToRun List that files to be run will be put in
 * @param _exitCode Int Exit code pointer.
 * @return Returns true if program can continue and false if not
 */
bool HandleArgs(int argNum, char** argPtr, List filesToRun, List flags, int* _exitCode);