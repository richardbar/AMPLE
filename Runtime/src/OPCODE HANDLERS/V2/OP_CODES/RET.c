#include <stdbool.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"
#include "Execution.h"

extern bool StopCurrentExecution;

bool RET_V2(MODE_FUNCTION_ARGUMENTS)
{
    return StopCurrentExecution = true;
}