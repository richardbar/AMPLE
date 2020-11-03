#include <stdbool.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V1.h"

#define ADD_CMP_FUNC(name, type)                                                                                    \
static bool CMP_REGISTER_NUM_ ##name (FUNCTION_ARGUMENTS)                                                           \
{                                                                                                                   \
    if (GetCapacityFromList(Registers) <= Arg1)                                                                     \
        return false;                                                                                               \
    *position += *(type*)GetElementFromList(Registers, Arg1) == Arg2;                                               \
    return true;                                                                                                    \
}                                                                                                                   \
static bool CMP_REGISTER_NUM_FAST_ ##name(FUNCTION_ARGUMENTS)                                                       \
{                                                                                                                   \
    *position += *(type*)GetElementFromList(Registers, Arg1) == Arg2;                                               \
    return true;                                                                                                    \
}                                                                                                                   \
                                                                                                                    \
static bool CMP_REGISTER_REGISTER_ ##name (FUNCTION_ARGUMENTS)                                                      \
{                                                                                                                   \
    if (GetCapacityFromList(Registers) <= Arg1 || GetCapacityFromList(Registers) <= Arg2)                           \
        return false;                                                                                               \
    *position += *(type*)GetElementFromList(Registers, Arg1) == *(type*)GetElementFromList(Registers, Arg2);        \
    return true;                                                                                                    \
}                                                                                                                   \
static bool CMP_REGISTER_REGISTER_FAST_ ##name(FUNCTION_ARGUMENTS)                                                  \
{                                                                                                                   \
    *position += *(type*)GetElementFromList(Registers, Arg1) == *(type*)GetElementFromList(Registers, Arg2);        \
    return true;                                                                                                    \
}                                                                                                                   \
                                                                                                                    \
static bool CMP_REGISTER_MEMORY_ ##name (FUNCTION_ARGUMENTS)                                                        \
{                                                                                                                   \
    if (GetCapacityFromList(Registers) <= Arg1 || GetCapacityFromList(Memory) <= Arg2)                              \
        return false;                                                                                               \
    *position += *(type*)GetElementFromList(Registers, Arg1) == *(type*)GetElementFromList(Memory, Arg2);           \
    return true;                                                                                                    \
}                                                                                                                   \
static bool CMP_REGISTER_MEMORY_FAST_ ##name(FUNCTION_ARGUMENTS)                                                    \
{                                                                                                                   \
    *position += *(type*)GetElementFromList(Registers, Arg1) == *(type*)GetElementFromList(Memory, Arg2);           \
    return true;                                                                                                    \
}                                                                                                                   \
                                                                                                                    \
static bool CMP_MEMORY_NUM_ ##name (FUNCTION_ARGUMENTS)                                                             \
{                                                                                                                   \
    if (GetCapacityFromList(Memory) <= Arg1)                                                                        \
        return false;                                                                                               \
    *position += *(type*)GetElementFromList(Memory, Arg1) == Arg2;                                                  \
    return true;                                                                                                    \
}                                                                                                                   \
static bool CMP_MEMORY_NUM_FAST_ ##name(FUNCTION_ARGUMENTS)                                                         \
{                                                                                                                   \
    *position += *(type*)GetElementFromList(Memory, Arg1) == Arg2;                                                  \
    return true;                                                                                                    \
}                                                                                                                   \
                                                                                                                    \
static bool CMP_MEMORY_REGISTER_ ##name (FUNCTION_ARGUMENTS)                                                        \
{                                                                                                                   \
    if (GetCapacityFromList(Memory) <= Arg1 || GetCapacityFromList(Registers) <= Arg2)                              \
        return false;                                                                                               \
    *position += *(type*)GetElementFromList(Memory, Arg1) == *(type*)GetElementFromList(Registers, Arg2);           \
    return true;                                                                                                    \
}                                                                                                                   \
static bool CMP_MEMORY_REGISTER_FAST_ ##name(FUNCTION_ARGUMENTS)                                                    \
{                                                                                                                   \
    *position += *(type*)GetElementFromList(Memory, Arg1) == *(type*)GetElementFromList(Registers, Arg2);           \
    return true;                                                                                                    \
}                                                                                                                   \
                                                                                                                    \
static bool CMP_MEMORY_MEMORY_ ##name (FUNCTION_ARGUMENTS)                                                          \
{                                                                                                                   \
    if (GetCapacityFromList(Memory) <= Arg1 || GetCapacityFromList(Memory) <= Arg2)                                 \
        return false;                                                                                               \
    *position += *(type*)GetElementFromList(Memory, Arg1) == *(type*)GetElementFromList(Memory, Arg2);              \
    return true;                                                                                                    \
}                                                                                                                   \
static bool CMP_MEMORY_MEMORY_FAST_ ##name(FUNCTION_ARGUMENTS)                                                      \
{                                                                                                                   \
    *position += *(type*)GetElementFromList(Memory, Arg1) == *(type*)GetElementFromList(Memory, Arg2);              \
    return true;                                                                                                    \
}


#define GET_CMP_FUNCS(name)                                                                                         \
CMP_REGISTER_NUM_ ##name ,                                                                                          \
CMP_REGISTER_NUM_FAST_ ##name ,                                                                                     \
CMP_REGISTER_REGISTER_ ##name ,                                                                                     \
CMP_REGISTER_REGISTER_FAST_ ##name ,                                                                                \
CMP_REGISTER_MEMORY_ ##name ,                                                                                       \
CMP_REGISTER_MEMORY_FAST_ ##name ,                                                                                  \
CMP_MEMORY_NUM_ ##name ,                                                                                            \
CMP_MEMORY_NUM_FAST_ ##name,                                                                                        \
CMP_MEMORY_REGISTER_ ##name,                                                                                        \
CMP_MEMORY_REGISTER_FAST_ ##name ,                                                                                  \
CMP_MEMORY_MEMORY_ ##name ,                                                                                         \
CMP_MEMORY_MEMORY_FAST_ ##name                                                                                      \

ADD_CMP_FUNC(UINT64, uint64_t)
ADD_CMP_FUNC(INT64, int64_t)
ADD_CMP_FUNC(UINT32, uint32_t)
ADD_CMP_FUNC(INT32, uint32_t)
ADD_CMP_FUNC(UINT16, uint16_t)
ADD_CMP_FUNC(INT16, int16_t)
ADD_CMP_FUNC(UINT8, uint8_t)
ADD_CMP_FUNC(INT8, uint8_t)



static bool (*CMP_MODES[])(ARGUMENT_TYPES) = {
        GET_CMP_FUNCS(UINT64),
        GET_CMP_FUNCS(INT64),
        GET_CMP_FUNCS(UINT32),
        GET_CMP_FUNCS(INT32),
        GET_CMP_FUNCS(UINT16),
        GET_CMP_FUNCS(INT16),
        GET_CMP_FUNCS(UINT8),
        GET_CMP_FUNCS(INT8)
};



bool CMP_V1(MODE_FUNCTION_ARGUMENTS)
{
    return CMP_MODES[Mode](PASS_ARGUMENTS);
}