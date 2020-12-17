#include <stdbool.h>
#include <stdint.h>

#include "AMPLE.h"
#include "CList.h"
#include "OPCODE HANDLERS/V2.h"

extern bool CHANGE_OP_VER_V1(MODE_FUNCTION_ARGUMENTS);
//extern bool HALT_V2(MODE_FUNCTION_ARGUMENTS);
//extern bool JMP_V2(MODE_FUNCTION_ARGUMENTS);
extern bool MOV_V2(MODE_FUNCTION_ARGUMENTS);

static bool (*Instructions[])(MODE_FUNCTION_ARGUMENTS) = {
    CHANGE_OP_VER_V1,
    NULL, //HALT_V2,
    NULL, //JMP_V2
    MOV_V2
};
static uint32_t NumberOfInstructions = 0;

bool HANDLE_OPCODE_V2(const uint8_t* OP_CODE, uint32_t* poition, CList Memory, CList Registers)
{
    if (!NumberOfInstructions)
        NumberOfInstructions = sizeof(Instructions) / sizeof(Instructions[0]);
    uint32_t opCode = *((uint32_t*)OP_CODE);
    if (NumberOfInstructions <= opCode)
        return false;
    return (Instructions[opCode]) ? Instructions[opCode](*((uint32_t*)(OP_CODE + 4)), *((uint64_t*)(OP_CODE + 8)), *((uint64_t*)(OP_CODE + 16)), *((uint64_t*)(OP_CODE + 24)), poition, Memory, Registers) : false;
}
