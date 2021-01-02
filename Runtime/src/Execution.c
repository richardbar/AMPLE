#include "AMPLE.h"
#include "Execution.h"
#include "HandleOP.h"
#include "main.h"

CStack ExecutionStack;

bool Execute(struct ExecutionStruct* byteCode, CList Memory, CList Registers)
{
    for (uint32_t i = byteCode->Position; i < byteCode->Size; i++)
    {
        if (!HANDLE_OPCODE(*((Instruction*)((uint64_t)byteCode->ByteCode + i * INSTRUCTION_LENGTH)), &i, Memory, Registers))
            return false;
    }
}

