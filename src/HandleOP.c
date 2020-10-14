#include "HandleOP.h"

extern bool HANDLE_OPCODE_V1(uint8_t*, uint32_t*, CList, CList);

bool (*OPCODE_HANDLER)(uint8_t*, uint32_t*, CList, CList) = HANDLE_OPCODE_V1;

bool HANDLE_OPCODE(uint8_t* OP_CODE, uint32_t* position, CList Memory, CList Registers)
{
    return OPCODE_HANDLER(OP_CODE, position, Memory, Registers);
}

bool SET_OPCODE_VERSION(uint32_t INSTRUCTION_VERSION)
{
    switch (INSTRUCTION_VERSION) {
        case 1:
            OPCODE_HANDLER = HANDLE_OPCODE_V1;
            break;
        default:
            return false;
    }
    return true;
}