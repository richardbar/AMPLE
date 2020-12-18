#include "HandleOP.h"

#include "OPCODE HANDLERS/V1.h"
#include "OPCODE HANDLERS/V2.h"

bool (*OPCODE_HANDLER)(const uint8_t*, uint32_t*, CList, CList) = HANDLE_OPCODE_V2;

bool HANDLE_OPCODE(const uint8_t* OP_CODE, uint32_t* position, CList Memory, CList Registers)
{
    return OPCODE_HANDLER(OP_CODE, position, Memory, Registers);
}

bool SET_OPCODE_VERSION(uint32_t INSTRUCTION_VERSION)
{
    switch (INSTRUCTION_VERSION) {
        case 1:
            OPCODE_HANDLER = HANDLE_OPCODE_V1;
            break;
        case 2:
            OPCODE_HANDLER = HANDLE_OPCODE_V2;
            break;
        default:
            return false;
    }
    return true;
}