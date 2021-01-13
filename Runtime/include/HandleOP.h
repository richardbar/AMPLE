#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "CList.h"
#include "Instruction.h"


bool SET_OPCODE_VERSION(uint32_t INSTRUCTION_VERSION);
bool HANDLE_OPCODE(Instruction OP_CODE, uint32_t* position, CList Memory, CList Registers);