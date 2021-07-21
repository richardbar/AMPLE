#pragma once

#include <AMPLE.h>

#include <stdbool.h>
#include <stdint.h>


/**
 * Initialize the Execution module
 * @return True if the initialization is successful and false if it fails
 */
bool ExecuteInitialize();


bool ExecuteExecute(uint8_t* programBytes, int64_t programSize, uint64_t programCounter);

/**
 * Clean Up the Execution module
 */
void ExecuteCleanUp();