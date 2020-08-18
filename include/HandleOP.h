#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "List.h"

bool SET_OPCODE_VERSION(uint32_t INSTRUCTION_VERSION);
bool HANDLE_OPCODE(uint8_t* OP_CODE, uint32_t* position, List Memory, List Registers);