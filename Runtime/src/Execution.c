#include "AMPLE.h"
#include "Execution.h"
#include "HandleOP.h"
#include "main.h"
#include "CStack.h"

CStack ExecutionStack = NULL;
bool StopCurrentExecution = false;

bool Execute(CList Memory, CList Registers)
{
    struct ExecutionStruct* byteCode = (struct ExecutionStruct*)FastGetElementFromStack(ExecutionStack);
    for (uint32_t i = byteCode->Position; (i < byteCode->Size) && !StopCurrentExecution; i++)
    {
        if (!HANDLE_OPCODE(*((Instruction*)((uint64_t)byteCode->ByteCode + i * INSTRUCTION_LENGTH)), &i, Memory, Registers))
            return false;
    }
    return true;
}

