#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <CList.h>

struct ExecutionStruct
{
    void* ByteCode;
    uint32_t Position;
    uint32_t Size;
};

bool Execute(CList Memory, CList Registers);