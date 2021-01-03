#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "CList.h"
#include "OPCODE HANDLERS/V2.h"

extern bool CHANGE_OP_VER_V1(MODE_FUNCTION_ARGUMENTS);


static bool (*Instructions[])(MODE_FUNCTION_ARGUMENTS) = {
    CHANGE_OP_VER_V1,
    HALT_V2,
    NULL, //JMP_V2
    MOV_V2,
    ADD_V2,
    SUB_V2,
    MULT_V2,
    DIV_V2,
    MOD_V2,
    LSHIFT_V2,
    RSHIFT_V2,
    AND_V2,
    OR_V2,
    XOR_V2,
    NOT_V2,
    CMPEQ_V2,
    CMPNE_V2,
    CMPLT_V2,
    CMPGT_V2,
    CMPLE_V2,
    CMPGE_V2,
    CALL_V2,
    RET_V2
};
static uint32_t NumberOfInstructions = 0;

bool HANDLE_OPCODE_V2(Instruction instruction, uint32_t* poition, CList Memory, CList Registers)
{
    if (!NumberOfInstructions)
        NumberOfInstructions = sizeof(Instructions) / sizeof(Instructions[0]);
    if (NumberOfInstructions <= instruction.OpCode)
        return false;
    return (Instructions[instruction.OpCode]) ? Instructions[instruction.OpCode](instruction.Mode, instruction.Arg1, instruction.Arg2, instruction.Arg3, poition, Memory, Registers) : false;
}
