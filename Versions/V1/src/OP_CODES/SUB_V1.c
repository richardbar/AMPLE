#include <stdbool.h>
#include <stdint.h>

#include "../../include/V1.h"

#define ADD_SUB_FUNC(name, type)                                                                                    \
static bool SUB_REGISTER_NUM_ ##name (FUNCTION_ARGUMENTS)                                                           \
{                                                                                                                   \
    if (GetCapacityFromList(Registers) <= Arg1)                                                                     \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Registers, Arg1) -= Arg2;                                                     \
}                                                                                                                   \
static bool SUB_REGISTER_NUM_FAST_ ##name(FUNCTION_ARGUMENTS)                                                       \
{                                                                                                                   \
    return *(type*)GetElementFromList(Registers, Arg1) -= Arg2;                                                     \
}                                                                                                                   \
static bool SUB_REGISTER_REGISTER_ ##name (FUNCTION_ARGUMENTS)                                                      \
{                                                                                                                   \
    if (GetCapacityFromList(Registers) <= Arg1 || GetCapacityFromList(Registers) <= Arg2)                           \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Registers, Arg1) -= *(type*)GetElementFromList(Registers, Arg2);              \
}                                                                                                                   \
static bool SUB_REGISTER_REGISTER_FAST_ ##name(FUNCTION_ARGUMENTS)                                                  \
{                                                                                                                   \
    return *(type*)GetElementFromList(Registers, Arg1) -= *(type*)GetElementFromList(Registers, Arg2);              \
}                                                                                                                   \
static bool SUB_REGISTER_MEMORY_ ##name (FUNCTION_ARGUMENTS)                                                        \
{                                                                                                                   \
    if (GetCapacityFromList(Registers) <= Arg1 || GetCapacityFromList(Memory) <= Arg2)                              \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Registers, Arg1) -= *(type*)GetElementFromList(Memory, Arg2);                 \
}                                                                                                                   \
static bool SUB_REGISTER_MEMORY_FAST_ ##name(FUNCTION_ARGUMENTS)                                                    \
{                                                                                                                   \
    return *(type*)GetElementFromList(Registers, Arg1) -= *(type*)GetElementFromList(Memory, Arg2);                 \
}                                                                                                                   \
                                                                                                                    \
                                                                                                                    \
static bool SUB_MEMORY_NUM_ ##name (FUNCTION_ARGUMENTS)                                                             \
{                                                                                                                   \
    if (GetCapacityFromList(Memory) <= Arg1)                                                                        \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Memory, Arg1) -= Arg2;                                                        \
}                                                                                                                   \
static bool SUB_MEMORY_NUM_FAST_ ##name(FUNCTION_ARGUMENTS)                                                         \
{                                                                                                                   \
    return *(type*)GetElementFromList(Memory, Arg1) -= Arg2;                                                        \
}                                                                                                                   \
static bool SUB_MEMORY_REGISTER_ ##name (FUNCTION_ARGUMENTS)                                                        \
{                                                                                                                   \
    if (GetCapacityFromList(Memory) <= Arg1 || GetCapacityFromList(Registers) <= Arg2)                              \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Memory, Arg1) -= *(type*)GetElementFromList(Registers, Arg2);                 \
}                                                                                                                   \
static bool SUB_MEMORY_REGISTER_FAST_ ##name(FUNCTION_ARGUMENTS)                                                    \
{                                                                                                                   \
    return *(type*)GetElementFromList(Memory, Arg1) -= *(type*)GetElementFromList(Registers, Arg2);                 \
}                                                                                                                   \
static bool SUB_MEMORY_MEMORY_ ##name (FUNCTION_ARGUMENTS)                                                          \
{                                                                                                                   \
    if (GetCapacityFromList(Memory) <= Arg1 || GetCapacityFromList(Memory) <= Arg2)                                 \
        return false;                                                                                               \
    return *(type*)GetElementFromList(Memory, Arg1) -= *(type*)GetElementFromList(Memory, Arg2);                    \
}                                                                                                                   \
static bool SUB_MEMORY_MEMORY_FAST_ ##name(FUNCTION_ARGUMENTS)                                                      \
{                                                                                                                   \
    return *(type*)GetElementFromList(Memory, Arg1) -= *(type*)GetElementFromList(Memory, Arg2);                    \
}

#define GET_SUB_FUNCS(name)                                                                                         \
SUB_REGISTER_NUM_ ##name ,                                                                                          \
SUB_REGISTER_NUM_FAST_ ##name ,                                                                                     \
SUB_REGISTER_REGISTER_ ##name ,                                                                                     \
SUB_REGISTER_REGISTER_FAST_ ##name ,                                                                                \
SUB_REGISTER_MEMORY_ ##name ,                                                                                       \
SUB_REGISTER_MEMORY_FAST_ ##name ,                                                                                  \
SUB_MEMORY_NUM_ ##name ,                                                                                            \
SUB_MEMORY_NUM_FAST_ ##name,                                                                                        \
SUB_MEMORY_REGISTER_ ##name,                                                                                        \
SUB_MEMORY_REGISTER_FAST_ ##name ,                                                                                  \
SUB_MEMORY_MEMORY_ ##name ,                                                                                         \
SUB_MEMORY_MEMORY_FAST_ ##name                                                                                      \

ADD_SUB_FUNC(UINT64, uint64_t)
ADD_SUB_FUNC(INT64, int64_t)
ADD_SUB_FUNC(UINT32, uint32_t)
ADD_SUB_FUNC(INT32, uint32_t)
ADD_SUB_FUNC(UINT16, uint16_t)
ADD_SUB_FUNC(INT16, int16_t)
ADD_SUB_FUNC(UINT8, uint8_t)
ADD_SUB_FUNC(INT8, uint8_t)



static bool (*SUB_MODES[])(ARGUMENT_TYPES) = {
        GET_SUB_FUNCS(UINT64),
        GET_SUB_FUNCS(INT64),
        GET_SUB_FUNCS(UINT32),
        GET_SUB_FUNCS(INT32),
        GET_SUB_FUNCS(UINT16),
        GET_SUB_FUNCS(INT16),
        GET_SUB_FUNCS(UINT8),
        GET_SUB_FUNCS(INT8)
};

bool SUB_V1(MODE_FUNCTION_ARGUMENTS)
{
    return SUB_MODES[Mode](PASS_ARGUMENTS);
}