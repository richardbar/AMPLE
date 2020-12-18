#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "CList.h"

bool SET_OPCODE_VERSION(uint32_t INSTRUCTION_VERSION);
bool HANDLE_OPCODE(const uint8_t* OP_CODE, uint32_t* position, CList Memory, CList Registers);