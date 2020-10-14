#pragma once

#include "CList.h"

#define ARGUMENT_TYPES uint64_t, uint64_t, uint32_t*, CList, CList
#define FUNCTION_ARGUMENTS uint64_t Arg1, uint64_t Arg2, uint32_t* position, CList Memory, CList Registers
#define MODE_FUNCTION_ARGUMENTS uint32_t Mode, FUNCTION_ARGUMENTS
#define PASS_ARGUMENTS Arg1, Arg2, position, Memory, Registers