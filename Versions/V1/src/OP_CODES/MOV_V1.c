#include <stdbool.h>
#include <stdint.h>

#include "V1.h"

#define ADD_MOV_FUNC(name, type)                                                                                    \
static bool MOV_REGISTER_NUM_ ##name (FUNCTION_ARGUMENTS)                                                           \
{                                                                                                                   \
    if (GetCapacityFromList(Registers) <= Arg1)                                                                     \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Registers, Arg1) = Arg2;                                                      \
}                                                                                                                   \
static bool MOV_REGISTER_NUM_FAST_ ##name(FUNCTION_ARGUMENTS)                                                       \
{                                                                                                                   \
    return *(type*)GetElementFromList(Registers, Arg1) = Arg2;                                                      \
}                                                                                                                   \
static bool MOV_REGISTER_REGISTER_ ##name (FUNCTION_ARGUMENTS)                                                      \
{                                                                                                                   \
    if (GetCapacityFromList(Registers) <= Arg1 || GetCapacityFromList(Registers) <= Arg2)                           \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Registers, Arg1) = *(type*)GetElementFromList(Registers, Arg2);               \
}                                                                                                                   \
static bool MOV_REGISTER_REGISTER_FAST_ ##name(FUNCTION_ARGUMENTS)                                                  \
{                                                                                                                   \
    return *(type*)GetElementFromList(Registers, Arg1) = *(type*)GetElementFromList(Registers, Arg2);               \
}                                                                                                                   \
static bool MOV_REGISTER_MEMORY_ ##name (FUNCTION_ARGUMENTS)                                                        \
{                                                                                                                   \
    if (GetCapacityFromList(Registers) <= Arg1 || GetCapacityFromList(Memory) <= Arg2)                              \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Registers, Arg1) = *(type*)GetElementFromList(Memory, Arg2);                  \
}                                                                                                                   \
static bool MOV_REGISTER_MEMORY_FAST_ ##name(FUNCTION_ARGUMENTS)                                                    \
{                                                                                                                   \
    return *(type*)GetElementFromList(Registers, Arg1) = *(type*)GetElementFromList(Memory, Arg2);                  \
}                                                                                                                   \
                                                                                                                    \
                                                                                                                    \
static bool MOV_MEMORY_NUM_ ##name (FUNCTION_ARGUMENTS)                                                             \
{                                                                                                                   \
    if (GetCapacityFromList(Memory) <= Arg1)                                                                        \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Memory, Arg1) = Arg2;                                                         \
}                                                                                                                   \
static bool MOV_MEMORY_NUM_FAST_ ##name(FUNCTION_ARGUMENTS)                                                         \
{                                                                                                                   \
    return *(type*)GetElementFromList(Memory, Arg1) = Arg2;                                                         \
}                                                                                                                   \
static bool MOV_MEMORY_REGISTER_ ##name (FUNCTION_ARGUMENTS)                                                        \
{                                                                                                                   \
    if (GetCapacityFromList(Memory) <= Arg1 || GetCapacityFromList(Registers) <= Arg2)                              \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Memory, Arg1) = *(type*)GetElementFromList(Registers, Arg2);                  \
}                                                                                                                   \
static bool MOV_MEMORY_REGISTER_FAST_ ##name(FUNCTION_ARGUMENTS)                                                    \
{                                                                                                                   \
    return *(type*)GetElementFromList(Memory, Arg1) = *(type*)GetElementFromList(Registers, Arg2);                  \
}                                                                                                                   \
static bool MOV_MEMORY_MEMORY_ ##name (FUNCTION_ARGUMENTS)                                                          \
{                                                                                                                   \
    if (GetCapacityFromList(Memory) <= Arg1 || GetCapacityFromList(Memory) <= Arg2)                                 \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Memory, Arg1) = *(type*)GetElementFromList(Memory, Arg2);                     \
}                                                                                                                   \
static bool MOV_MEMORY_MEMORY_FAST_ ##name(FUNCTION_ARGUMENTS)                                                      \
{                                                                                                                   \
    return *(type*)GetElementFromList(Memory, Arg1) = *(type*)GetElementFromList(Memory, Arg2);                     \
}

#define GET_MOV_FUNCS(name)                                                                                         \
MOV_REGISTER_NUM_ ##name ,                                                                                          \
MOV_REGISTER_NUM_FAST_ ##name ,                                                                                     \
MOV_REGISTER_REGISTER_ ##name ,                                                                                     \
MOV_REGISTER_REGISTER_FAST_ ##name ,                                                                                \
MOV_REGISTER_MEMORY_ ##name ,                                                                                       \
MOV_REGISTER_MEMORY_FAST_ ##name ,                                                                                  \
MOV_MEMORY_NUM_ ##name ,                                                                                            \
MOV_MEMORY_NUM_FAST_ ##name,                                                                                        \
MOV_MEMORY_REGISTER_ ##name,                                                                                        \
MOV_MEMORY_REGISTER_FAST_ ##name ,                                                                                  \
MOV_MEMORY_MEMORY_ ##name ,                                                                                         \
MOV_MEMORY_MEMORY_FAST_ ##name                                                                                      \

ADD_MOV_FUNC(UINT64, uint64_t)
ADD_MOV_FUNC(INT64, int64_t)
ADD_MOV_FUNC(UINT32, uint32_t)
ADD_MOV_FUNC(INT32, int32_t)
ADD_MOV_FUNC(UINT16, uint16_t)
ADD_MOV_FUNC(INT16, int16_t)
ADD_MOV_FUNC(UINT8, uint8_t)
ADD_MOV_FUNC(INT8, int8_t)

bool (*MOV_MODES[])(ARGUMENT_TYPES) = {
        GET_MOV_FUNCS(UINT64),
        GET_MOV_FUNCS(INT64),
        GET_MOV_FUNCS(UINT32),
        GET_MOV_FUNCS(INT32),
        GET_MOV_FUNCS(UINT16),
        GET_MOV_FUNCS(INT16),
        GET_MOV_FUNCS(UINT8),
        GET_MOV_FUNCS(INT8)
};

bool MOV_V1(MODE_FUNCTION_ARGUMENTS)
{
    return MOV_MODES[Mode](PASS_ARGUMENTS);
}