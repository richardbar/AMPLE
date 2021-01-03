#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "CStack.h"
#include "OPCODE HANDLERS/V2.h"
#include "Execution.h"

extern CStack ExecutionStack;
extern bool StopCurrentExecution;

static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)

static INLINE bool CALL(uint32_t position, CList Memory, CList Registers)
{
    struct ExecutionStruct* lastRun = (struct ExecutionStruct*)GetElementFromStack(ExecutionStack);
    struct ExecutionStruct* newRun = (struct ExecutionStruct*)malloc(sizeof(struct ExecutionStruct));

    newRun->ByteCode = lastRun->ByteCode;
    newRun->Size = lastRun->Size;
    newRun->Position = position;

    InsertElementToStack(ExecutionStack, newRun);

    bool returnVal = Execute(Memory, Registers);
    RemoveElementFromStack(ExecutionStack);
    free(newRun);

    StopCurrentExecution = false;

    return returnVal;
}

static bool CALL_NUM(FUNCTION_ARGUMENTS)
{
    return CALL(Arg1, Memory, Registers);
}
static bool CALL_REGISTER_N(FUNCTION_ARGUMENTS)
{
    CHECK_SIZE_OF_REGISTER();
    if (sizeOfRegisters <= Arg1)
        return false;
    return CALL(*((uint32_t*)GetElementFromList(Registers, Arg1)), Memory, Registers);
}
static bool CALL_REGISTER_F(FUNCTION_ARGUMENTS)
{
    return CALL(*((uint32_t*)GetElementFromList(Registers, Arg1)), Memory, Registers);
}
static bool CALL_MEMORY_N(FUNCTION_ARGUMENTS)
{
    CHECK_SIZE_OF_MEMORY();
    if (sizeOfMemory <= Arg1)
        return false;
    return CALL(*((uint32_t*)GetElementFromList(Memory, Arg1)), Memory, Registers);
}
static bool CALL_MEMORY_F(FUNCTION_ARGUMENTS)
{
    return CALL(*((uint32_t*)GetElementFromList(Memory, Arg1)), Memory, Registers);
}


static bool (*CALL_MODES[])(ARGUMENT_TYPES) = {
        NULL,
        CALL_NUM,                                                           // 0b0000000001
        CALL_REGISTER_N,                                                    // 0b0000000010
        CALL_REGISTER_F,                                                    // 0b0000000011
        CALL_MEMORY_N,                                                      // 0b0000000100
        CALL_MEMORY_F                                                       // 0b0000000101
};



bool CALL_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (CALL_MODES[Mode]) ? CALL_MODES[Mode](PASS_ARGUMENTS) : false;
}