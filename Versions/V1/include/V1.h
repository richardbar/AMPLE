#pragma once

#include "CList.h"
#include "CStack.h"
#include "Instruction.h"

#include "AMPLE.h"

#define ARGUMENT_TYPES uint64_t, uint64_t,uint64_t,  uint32_t*, CList, CList, CStack, bool*, bool(*)(CList, CList)
#define FUNCTION_ARGUMENTS uint64_t Arg1, uint64_t Arg2, uint64_t Arg3, uint32_t* position, CList Memory, CList Registers, CStack ExecutionStack, bool* StopCurrentExecution, bool(*Execute)(CList, CList)
#define MODE_FUNCTION_ARGUMENTS uint32_t Mode, FUNCTION_ARGUMENTS
#define PASS_ARGUMENTS Arg1, Arg2, Arg3, position, Memory, Registers, ExecutionStack, StopCurrentExecution, Execute

EXPORT bool HANDLE_OPCODE(Instruction instruction, uint32_t* poition, CList Memory, CList Registers, CStack ExecutionStack, bool* StopCurrentExecution, bool(*Execute)(CList, CList));