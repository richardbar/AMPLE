#pragma once

#include <stdbool.h>

#include "CList.h"

/**
 * @param argNum argNum Number of arguments to be parsed
 * @param argPtr Pointer to array of string pointers to be parsed
 * @param filesToRun CList that files to be run will be put in
 * @param _exitCode Int Exit code pointer.
 * @return Returns true if program can continue and false if not
 */
bool HandleArgs(int argNum, char** argPtr, CList filesToRun, CList flags, int* _exitCode);