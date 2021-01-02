#pragma once

#include <stdbool.h>

#include "CStack.h"

struct ExecutionStruct
{
    void* ByteCode;
    uint32_t Position;
    uint32_t Size;
};

bool Execute(struct ExecutionStruct* byteCode, CList Memory, CList Registers);