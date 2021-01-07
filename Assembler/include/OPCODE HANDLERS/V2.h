#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "LineParser.h"

#define ARGS struct Instruction* instruction, struct Binary* binary

bool HALT_V2(ARGS);
bool MOV_V2(ARGS);
bool ADD_V2(ARGS);
bool SUB_V2(ARGS);
bool MULT_V2(ARGS);
bool DIV_V2(ARGS);
bool MOD_V2(ARGS);
bool LSHIFT_V2(ARGS);
bool RSHIFT_V2(ARGS);
bool AND_V2(ARGS);
bool OR_V2(ARGS);
bool XOR_V2(ARGS);
bool NOT_V2(ARGS);