#include <stdbool.h>
#include <stdint.h>

#include "CList.h"
#include "OPCODE HANDLERS/V1.h"

extern bool HALT_V1(MODE_FUNCTION_ARGUMENTS);
extern bool JMP_V1(MODE_FUNCTION_ARGUMENTS);
extern bool MOV_V1(MODE_FUNCTION_ARGUMENTS);
extern bool ADD_V1(MODE_FUNCTION_ARGUMENTS);
extern bool SUB_V1(MODE_FUNCTION_ARGUMENTS);
extern bool MULT_V1(MODE_FUNCTION_ARGUMENTS);
extern bool DIV_V1(MODE_FUNCTION_ARGUMENTS);
extern bool CMP_V1(MODE_FUNCTION_ARGUMENTS);
extern bool CHANGE_OP_VER_V1(MODE_FUNCTION_ARGUMENTS);

bool (*Instructions[])(MODE_FUNCTION_ARGUMENTS) = {
        CHANGE_OP_VER_V1,
        HALT_V1,
        JMP_V1,
        MOV_V1,
        ADD_V1,
        SUB_V1,
        MULT_V1,
        DIV_V1,
        CMP_V1
};

bool HANDLE_OPCODE_V1(uint8_t* OP_CODE, uint32_t* position, CList Memory, CList Registers)
{
    uint32_t opCode = *(uint32_t*)OP_CODE;
    return Instructions[opCode](*(uint32_t*)(OP_CODE + 4), *(uint64_t*)(OP_CODE + 8), *(uint64_t*)(OP_CODE + 16), *(uint64_t*)(OP_CODE + 24), position, Memory, Registers);
}