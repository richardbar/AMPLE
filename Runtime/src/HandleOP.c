#include "HandleOP.h"

#include "Instruction.h"

bool (*OPCODE_HANDLER)(Instruction, uint32_t*, CList, CList) = NULL;

bool HANDLE_OPCODE(Instruction instruction, uint32_t* position, CList Memory, CList Registers)
{
    return OPCODE_HANDLER(instruction, position, Memory, Registers);
}

bool SET_OPCODE_VERSION(uint32_t INSTRUCTION_VERSION)
{
    switch (INSTRUCTION_VERSION) {
        case 1:
            OPCODE_HANDLER = NULL;
            break;
        case 2:
            OPCODE_HANDLER = NULL;
            break;
        default:
            return false;
    }
    return true;
}