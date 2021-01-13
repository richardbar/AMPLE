#include <stdbool.h>
#include <stdint.h>

#include "V2.h"

extern bool StopCurrentExecution;

bool RET_V2(MODE_FUNCTION_ARGUMENTS)
{
    *StopCurrentExecution = true;
    return true;
}