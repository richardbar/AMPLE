#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "LineParser.h"

#define ARGS struct Instruction* instruction, struct Binary* binary

bool MOV_V2(ARGS);
bool ADD_V2(ARGS);
bool SUB_V2(ARGS);