#include <stdbool.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V1.h"

static bool ADD_REGISTER_NUM_UINT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Registers) <= Arg1)
        return false;
    uint64_t* pos = GetElementFromList(Registers, Arg1);
    return *pos += Arg2;
}

static bool ADD_REGISTER_NUM_FAST_UINT64(FUNCTION_ARGUMENTS)
{
    return *(uint64_t*)GetElementFromList(Registers, Arg1) += Arg2;
}


static bool ADD_REGISTER_REGISTER_UINT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Registers) <= (Arg1 < Arg2) ? Arg2 : Arg1)
        return false;
    uint64_t* pos1 = GetElementFromList(Registers, Arg1);
    uint64_t* pos2 = GetElementFromList(Registers, Arg2);
    return *pos1 += *pos2;
}

static bool ADD_REGISTER_REGISTER_FAST_UINT64(FUNCTION_ARGUMENTS)
{
    return *(uint64_t*)GetElementFromList(Registers, Arg1) += *(uint64_t*)GetElementFromList(Registers, Arg2);
}


static bool ADD_REGISTER_MEMORY_UINT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Registers) <= Arg1 || GetCapacityFromList(Memory) <= Arg2)
        return false;
    uint64_t* pos1 = GetElementFromList(Registers, Arg1);
    uint64_t* pos2 = GetElementFromList(Memory, Arg2);
    return *pos1 += *pos2;
}

static bool ADD_REGISTER_MEMORY_FAST_UINT64(FUNCTION_ARGUMENTS)
{
    return *(uint64_t*)GetElementFromList(Registers, Arg1) += *(uint64_t*)GetElementFromList(Memory, Arg2);
}


static bool ADD_MEMORY_NUM_UINT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= Arg1)
        return false;
    uint64_t* pos = GetElementFromList(Memory, Arg1);
    return *pos += Arg2;
}

static bool ADD_MEMORY_NUM_FAST_UINT64(FUNCTION_ARGUMENTS)
{
    return *(uint64_t*)GetElementFromList(Memory, Arg1) += Arg2;
}


static bool ADD_MEMORY_REGISTER_UINT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= Arg1 || GetCapacityFromList(Registers) <= Arg2)
        return false;
    uint64_t* pos1 = GetElementFromList(Memory, Arg1);
    uint64_t* pos2 = GetElementFromList(Registers, Arg2);
    return *pos1 += *pos2;
}

static bool ADD_MEMORY_REGISTER_FAST_UINT64(FUNCTION_ARGUMENTS)
{
    return *(uint64_t*)GetElementFromList(Memory, Arg1) += *(uint64_t*)GetElementFromList(Registers, Arg2);
}


static bool ADD_MEMORY_MEMORY_UINT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= (Arg1 < Arg2) ? Arg2 : Arg1)
        return false;
    uint64_t* pos1 = GetElementFromList(Memory, Arg1);
    uint64_t* pos2 = GetElementFromList(Memory, Arg2);
    return *pos1 += *pos2;
}

static bool ADD_MEMORY_MEMORY_FAST_UINT64(FUNCTION_ARGUMENTS)
{
    return *(uint64_t*)GetElementFromList(Memory, Arg1) += *(uint64_t*)GetElementFromList(Memory, Arg2);
}



static bool ADD_REGISTER_NUM_INT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Registers) <= Arg1)
        return false;
    int64_t* pos = GetElementFromList(Registers, Arg1);
    return *pos += Arg2;
}

static bool ADD_REGISTER_NUM_FAST_INT64(FUNCTION_ARGUMENTS)
{
    return *(int64_t*)GetElementFromList(Registers, Arg1) += Arg2;
}


static bool ADD_REGISTER_REGISTER_INT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Registers) <= (Arg1 < Arg2) ? Arg2 : Arg1)
        return false;
    int64_t* pos1 = GetElementFromList(Registers, Arg1);
    int64_t* pos2 = GetElementFromList(Registers, Arg2);
    return *pos1 += *pos2;
}

static bool ADD_REGISTER_REGISTER_FAST_INT64(FUNCTION_ARGUMENTS)
{
    return *(int64_t*)GetElementFromList(Registers, Arg1) += *(int64_t*)GetElementFromList(Registers, Arg2);
}


static bool ADD_REGISTER_MEMORY_INT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Registers) <= Arg1 || GetCapacityFromList(Memory) <= Arg2)
        return false;
    int64_t* pos1 = GetElementFromList(Registers, Arg1);
    int64_t* pos2 = GetElementFromList(Memory, Arg2);
    return *pos1 += *pos2;
}

static bool ADD_REGISTER_MEMORY_FAST_INT64(FUNCTION_ARGUMENTS)
{
    return *(int64_t*)GetElementFromList(Registers, Arg1) += *(int64_t*)GetElementFromList(Memory, Arg2);
}


static bool ADD_MEMORY_NUM_INT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= Arg1)
        return false;
    int64_t* pos = GetElementFromList(Memory, Arg1);
    return *pos += Arg2;
}

static bool ADD_MEMORY_NUM_FAST_INT64(FUNCTION_ARGUMENTS)
{
    return *(int64_t*)GetElementFromList(Memory, Arg1) += Arg2;
}


static bool ADD_MEMORY_REGISTER_INT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= Arg1 || GetCapacityFromList(Registers) <= Arg2)
        return false;
    int64_t* pos1 = GetElementFromList(Memory, Arg1);
    int64_t* pos2 = GetElementFromList(Registers, Arg2);
    return *pos1 += *pos2;
}

static bool ADD_MEMORY_REGISTER_FAST_INT64(FUNCTION_ARGUMENTS)
{
    return *(int64_t*)GetElementFromList(Memory, Arg1) += *(int64_t*)GetElementFromList(Registers, Arg2);
}


static bool ADD_MEMORY_MEMORY_INT64(FUNCTION_ARGUMENTS)
{
    if (GetCapacityFromList(Memory) <= (Arg1 < Arg2) ? Arg2 : Arg1)
        return false;
    int64_t* pos1 = GetElementFromList(Memory, Arg1);
    int64_t* pos2 = GetElementFromList(Memory, Arg2);
    return *pos1 += *pos2;
}

static bool ADD_MEMORY_MEMORY_FAST_INT64(FUNCTION_ARGUMENTS)
{
    return *(int64_t*)GetElementFromList(Memory, Arg1) += *(int64_t*)GetElementFromList(Memory, Arg2);
}



static bool (*ADD_MODES[])(ARGUMENT_TYPES) = {
        ADD_REGISTER_NUM_UINT64,
        ADD_REGISTER_REGISTER_UINT64,
        ADD_REGISTER_MEMORY_UINT64,
        ADD_MEMORY_NUM_UINT64,
        ADD_MEMORY_REGISTER_UINT64,
        ADD_MEMORY_MEMORY_UINT64,

        ADD_REGISTER_NUM_FAST_UINT64,
        ADD_REGISTER_REGISTER_FAST_UINT64,
        ADD_REGISTER_MEMORY_FAST_UINT64,
        ADD_MEMORY_NUM_FAST_UINT64,
        ADD_MEMORY_REGISTER_FAST_UINT64,
        ADD_MEMORY_MEMORY_FAST_UINT64,

        ADD_REGISTER_NUM_INT64,
        ADD_REGISTER_REGISTER_INT64,
        ADD_REGISTER_MEMORY_INT64,
        ADD_MEMORY_NUM_INT64,
        ADD_MEMORY_REGISTER_INT64,
        ADD_MEMORY_MEMORY_INT64,

        ADD_REGISTER_NUM_FAST_INT64,
        ADD_REGISTER_REGISTER_FAST_INT64,
        ADD_REGISTER_MEMORY_FAST_INT64,
        ADD_MEMORY_NUM_FAST_INT64,
        ADD_MEMORY_REGISTER_FAST_INT64,
        ADD_MEMORY_MEMORY_FAST_INT64
};



bool ADD_V1(MODE_FUNCTION_ARGUMENTS)
{
    return ADD_MODES[Mode](PASS_ARGUMENTS);
}