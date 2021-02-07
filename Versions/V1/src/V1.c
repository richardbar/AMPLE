#include <stdbool.h>
#include <stdint.h>

#include "CList.h"
#include "CStack.h"
#include "V1.h"

extern bool HALT_V1(MODE_FUNCTION_ARGUMENTS);
extern bool JMP_V1(MODE_FUNCTION_ARGUMENTS);
extern bool MOV_V1(MODE_FUNCTION_ARGUMENTS);
extern bool ADD_V1(MODE_FUNCTION_ARGUMENTS);
extern bool SUB_V1(MODE_FUNCTION_ARGUMENTS);
extern bool MULT_V1(MODE_FUNCTION_ARGUMENTS);
extern bool DIV_V1(MODE_FUNCTION_ARGUMENTS);

static bool (*Instructions[])(MODE_FUNCTION_ARGUMENTS) = {
        NULL,
        HALT_V1,
        JMP_V1,
        MOV_V1,
        ADD_V1,
        SUB_V1,
        MULT_V1,
        DIV_V1
};
static uint32_t NumberOfInstructions = 0;

bool HANDLE_OPCODE(Instruction instruction, uint32_t* position, CList Memory, CList Registers, CStack ExecutionStack, bool* StopCurrentExecution, bool(*Execute)(CList, CList))
{
    if (!NumberOfInstructions)
        NumberOfInstructions = sizeof(Instructions) / sizeof(Instructions[0]);
    if (NumberOfInstructions <= instruction.Mode)
        return false;
    return (Instructions[instruction.OpCode]) ? Instructions[instruction.OpCode](instruction.OpCode, instruction.Arg1, instruction.Arg2, instruction.Arg3, position, Memory, Registers, ExecutionStack, StopCurrentExecution, Execute) : false;
}