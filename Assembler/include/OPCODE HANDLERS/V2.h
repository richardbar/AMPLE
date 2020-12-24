#pragma once

#include "OPCodeHandler.h"

bool HandleAssembly_V2(LINE_ARGS);

bool AssembleMOV(LINE_ARGS);
bool AssembleADD(LINE_ARGS);
bool AssembleSUB(LINE_ARGS);
bool AssembleMULT(LINE_ARGS);
bool AssembleDIV(LINE_ARGS);
bool AssembleMOD(LINE_ARGS);
bool AssembleLSHIFT(LINE_ARGS);
bool AssembleRSHIFT(LINE_ARGS);
bool AssembleAND(LINE_ARGS);
bool AssembleOR(LINE_ARGS);