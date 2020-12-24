#pragma once

#include "CList.h"
#include "OPCODE HANDLERS/Instruction.h"



#define GLUE(x, y) x##y



#define ARGUMENT_TYPES uint64_t, uint64_t,uint64_t,  uint32_t*, CList, CList
#define FUNCTION_ARGUMENTS uint64_t Arg1, uint64_t Arg2, uint64_t Arg3, uint32_t* position, CList Memory, CList Registers
#define MODE_FUNCTION_ARGUMENTS uint32_t Mode, FUNCTION_ARGUMENTS
#define PASS_ARGUMENTS Arg1, Arg2, Arg3, position, Memory, Registers



#define COMPARISON_FUNCS(name, width, castType, operator)                                                                                           \
static bool GLUE(CMP ##name ##width, _NUM_REGISTER_N)(FUNCTION_ARGUMENTS)                                                                           \
{                                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                                       \
    if (sizeOfRegisters <= Arg1)                                                                                                                    \
        return false;                                                                                                                               \
    return *position += (*((castType*)GetElementFromList(Registers, Arg1)) operator (castType)Arg2);                                                \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _REGISTER_REGISTER_N_N)(FUNCTION_ARGUMENTS)                                                                    \
{                                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                                       \
    if (sizeOfRegisters <= ((Arg1 > Arg2) ? Arg1 : Arg2))                                                                                           \
        return false;                                                                                                                               \
    return *position += (*((castType*)GetElementFromList(Registers, Arg1)) operator *((castType*)GetElementFromList(Registers, Arg2)));             \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _REGISTER_REGISTER_F_N)(FUNCTION_ARGUMENTS)                                                                    \
{                                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                                       \
    if (sizeOfRegisters <= Arg1)                                                                                                                    \
        return false;                                                                                                                               \
    return *position += (*((castType*)GetElementFromList(Registers, Arg1)) operator *((castType*)FastGetElementFromList(Registers, Arg2)));         \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _MEMORY_REGISTER_N_N)(FUNCTION_ARGUMENTS)                                                                      \
{                                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                                       \
    CHECK_SIZE_OF_MEMORY();                                                                                                                         \
    if ((sizeOfRegisters <= Arg1) && (sizeOfMemory <= Arg2))                                                                                        \
        return false;                                                                                                                               \
    return *position += (*((castType*)GetElementFromList(Registers, Arg1)) operator *((castType*)GetElementFromList(Memory, Arg2)));                \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _MEMORY_REGISTER_F_N)(FUNCTION_ARGUMENTS)                                                                      \
{                                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                                       \
    if (sizeOfRegisters <= Arg1)                                                                                                                    \
        return false;                                                                                                                               \
    return *position += (*((castType*)GetElementFromList(Registers, Arg1)) operator *((castType*)FastGetElementFromList(Memory, Arg2)));            \
}                                                                                                                                                   \
                                                                                                                                                    \
                                                                                                                                                    \
                                                                                                                                                    \
static bool GLUE(CMP ##name ##width, _NUM_REGISTER_F)(FUNCTION_ARGUMENTS)                                                                           \
{                                                                                                                                                   \
    return *position += (*((castType*)FastGetElementFromList(Registers, Arg1)) operator (castType)Arg2);                                            \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _REGISTER_REGISTER_N_F)(FUNCTION_ARGUMENTS)                                                                    \
{                                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                                       \
    if (sizeOfRegisters <= Arg2)                                                                                                                    \
        return false;                                                                                                                               \
    return *position += (*((castType*)FastGetElementFromList(Registers, Arg1)) operator *((castType*)GetElementFromList(Registers, Arg2)));         \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _REGISTER_REGISTER_F_F)(FUNCTION_ARGUMENTS)                                                                    \
{                                                                                                                                                   \
    return *position += (*((castType*)FastGetElementFromList(Registers, Arg1)) operator *((castType*)FastGetElementFromList(Registers, Arg2)));     \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _MEMORY_REGISTER_N_F)(FUNCTION_ARGUMENTS)                                                                      \
{                                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                                         \
    if (sizeOfMemory <= Arg2)                                                                                                                       \
        return false;                                                                                                                               \
    return *position += (*((castType*)FastGetElementFromList(Registers, Arg1)) operator *((castType*)GetElementFromList(Memory, Arg2)));            \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _MEMORY_REGISTER_F_F)(FUNCTION_ARGUMENTS)                                                                      \
{                                                                                                                                                   \
    return *position += (*((castType*)FastGetElementFromList(Registers, Arg1)) operator *((castType*)FastGetElementFromList(Memory, Arg2)));        \
}                                                                                                                                                   \
                                                                                                                                                    \
                                                                                                                                                    \
                                                                                                                                                    \
static bool GLUE(CMP ##name ##width, _NUM_MEMORY_N)(FUNCTION_ARGUMENTS)                                                                             \
{                                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                                         \
    if (sizeOfMemory <= Arg1)                                                                                                                       \
        return false;                                                                                                                               \
    return *position += (*((castType*)GetElementFromList(Memory, Arg1)) operator (castType)Arg2);                                                   \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _REGISTER_MEMORY_N_N)(FUNCTION_ARGUMENTS)                                                                      \
{                                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                                       \
    CHECK_SIZE_OF_MEMORY();                                                                                                                         \
    if ((sizeOfMemory <= Arg1) && (sizeOfRegisters <= Arg2))                                                                                        \
        return false;                                                                                                                               \
    return *position += (*((castType*)GetElementFromList(Memory, Arg1)) operator *((castType*)GetElementFromList(Registers, Arg2)));                \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _REGISTER_MEMORY_F_N)(FUNCTION_ARGUMENTS)                                                                      \
{                                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                                         \
    if (sizeOfMemory <= Arg1)                                                                                                                       \
        return false;                                                                                                                               \
    return *position += (*((castType*)GetElementFromList(Memory, Arg1)) operator *((castType*)FastGetElementFromList(Registers, Arg2)));            \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _MEMORY_MEMORY_N_N)(FUNCTION_ARGUMENTS)                                                                        \
{                                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                                         \
    if (sizeOfMemory <= ((Arg1 > Arg2) ? Arg1 : Arg2))                                                                                              \
        return false;                                                                                                                               \
    return *position += (*((castType*)GetElementFromList(Memory, Arg1)) operator *((castType*)GetElementFromList(Memory, Arg2)));                   \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _MEMORY_MEMORY_F_N)(FUNCTION_ARGUMENTS)                                                                        \
{                                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                                         \
    if (sizeOfMemory <= Arg1)                                                                                                                       \
        return false;                                                                                                                               \
    return *position += (*((castType*)GetElementFromList(Memory, Arg1)) operator *((castType*)FastGetElementFromList(Memory, Arg2)));               \
}                                                                                                                                                   \
                                                                                                                                                    \
                                                                                                                                                    \
                                                                                                                                                    \
static bool GLUE(CMP ##name ##width, _NUM_MEMORY_F)(FUNCTION_ARGUMENTS)                                                                             \
{                                                                                                                                                   \
    return *position += (*((castType*)FastGetElementFromList(Memory, Arg1)) operator (castType)Arg2);                                               \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _REGISTER_MEMORY_N_F)(FUNCTION_ARGUMENTS)                                                                      \
{                                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                                       \
    if (sizeOfRegisters <= Arg2)                                                                                                                    \
        return false;                                                                                                                               \
    return *position += (*((castType*)FastGetElementFromList(Memory, Arg1)) operator *((castType*)GetElementFromList(Registers, Arg2)));            \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _REGISTER_MEMORY_F_F)(FUNCTION_ARGUMENTS)                                                                      \
{                                                                                                                                                   \
    return *position += (*((castType*)FastGetElementFromList(Memory, Arg1)) operator *((castType*)FastGetElementFromList(Registers, Arg2)));        \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _MEMORY_MEMORY_N_F)(FUNCTION_ARGUMENTS)                                                                        \
{                                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                                         \
    if (sizeOfMemory <= Arg2)                                                                                                                       \
        return false;                                                                                                                               \
    return *position += (*((castType*)FastGetElementFromList(Memory, Arg1)) operator *((castType*)GetElementFromList(Memory, Arg2)));               \
}                                                                                                                                                   \
static bool GLUE(CMP ##name ##width, _MEMORY_MEMORY_F_F)(FUNCTION_ARGUMENTS)                                                                        \
{                                                                                                                                                   \
    return *position += (*((castType*)FastGetElementFromList(Memory, Arg1)) operator *((castType*)FastGetElementFromList(Memory, Arg2)));           \
}



#define ASSIGNMENT_FUNCS(name, width, castType, operator)                                                                           \
static bool GLUE(name ##width, _NUM_REGISTER_N)(FUNCTION_ARGUMENTS)                                                                 \
{                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                       \
    if (sizeOfRegisters <= Arg1)                                                                                                    \
        return false;                                                                                                               \
    return *((castType*)GetElementFromList(Registers, Arg1)) operator (castType)Arg2;                                               \
}                                                                                                                                   \
static bool GLUE(name ##width, _REGISTER_REGISTER_N_N)(FUNCTION_ARGUMENTS)                                                          \
{                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                       \
    if (sizeOfRegisters <= ((Arg1 > Arg2) ? Arg1 : Arg2))                                                                           \
        return false;                                                                                                               \
    return *((castType*)GetElementFromList(Registers, Arg1)) operator *((castType*)GetElementFromList(Registers, Arg2));            \
}                                                                                                                                   \
static bool GLUE(name ##width, _REGISTER_REGISTER_F_N)(FUNCTION_ARGUMENTS)                                                          \
{                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                       \
    if (sizeOfRegisters <= Arg1)                                                                                                    \
        return false;                                                                                                               \
    return *((castType*)GetElementFromList(Registers, Arg1)) operator *((castType*)FastGetElementFromList(Registers, Arg2));        \
}                                                                                                                                   \
static bool GLUE(name ##width, _MEMORY_REGISTER_N_N)(FUNCTION_ARGUMENTS)                                                            \
{                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                       \
    CHECK_SIZE_OF_MEMORY();                                                                                                         \
    if ((sizeOfRegisters <= Arg1) && (sizeOfMemory <= Arg2))                                                                        \
        return false;                                                                                                               \
    return *((castType*)GetElementFromList(Registers, Arg1)) operator *((castType*)GetElementFromList(Memory, Arg2));               \
}                                                                                                                                   \
static bool GLUE(name ##width, _MEMORY_REGISTER_F_N)(FUNCTION_ARGUMENTS)                                                            \
{                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                       \
    if (sizeOfRegisters <= Arg1)                                                                                                    \
        return false;                                                                                                               \
    return *((castType*)GetElementFromList(Registers, Arg1)) operator *((castType*)FastGetElementFromList(Memory, Arg2));           \
}                                                                                                                                   \
                                                                                                                                    \
                                                                                                                                    \
                                                                                                                                    \
static bool GLUE(name ##width, _NUM_REGISTER_F)(FUNCTION_ARGUMENTS)                                                                 \
{                                                                                                                                   \
    return *((castType*)FastGetElementFromList(Registers, Arg1)) operator (castType)Arg2;                                           \
}                                                                                                                                   \
static bool GLUE(name ##width, _REGISTER_REGISTER_N_F)(FUNCTION_ARGUMENTS)                                                          \
{                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                       \
    if (sizeOfRegisters <= Arg2)                                                                                                    \
        return false;                                                                                                               \
    return *((castType*)FastGetElementFromList(Registers, Arg1)) operator *((castType*)GetElementFromList(Registers, Arg2));        \
}                                                                                                                                   \
static bool GLUE(name ##width, _REGISTER_REGISTER_F_F)(FUNCTION_ARGUMENTS)                                                          \
{                                                                                                                                   \
    return *((castType*)FastGetElementFromList(Registers, Arg1)) operator *((castType*)FastGetElementFromList(Registers, Arg2));    \
}                                                                                                                                   \
static bool GLUE(name ##width, _MEMORY_REGISTER_N_F)(FUNCTION_ARGUMENTS)                                                            \
{                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                         \
    if (sizeOfMemory <= Arg2)                                                                                                       \
        return false;                                                                                                               \
    return *((castType*)FastGetElementFromList(Registers, Arg1)) operator *((castType*)GetElementFromList(Memory, Arg2));           \
}                                                                                                                                   \
static bool GLUE(name ##width, _MEMORY_REGISTER_F_F)(FUNCTION_ARGUMENTS)                                                            \
{                                                                                                                                   \
    return *((castType*)FastGetElementFromList(Registers, Arg1)) operator *((castType*)FastGetElementFromList(Memory, Arg2));       \
}                                                                                                                                   \
                                                                                                                                    \
                                                                                                                                    \
                                                                                                                                    \
static bool GLUE(name ##width, _NUM_MEMORY_N)(FUNCTION_ARGUMENTS)                                                                   \
{                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                         \
    if (sizeOfMemory <= Arg1)                                                                                                       \
        return false;                                                                                                               \
    return *((castType*)GetElementFromList(Memory, Arg1)) operator (castType)Arg2;                                                  \
}                                                                                                                                   \
static bool GLUE(name ##width, _REGISTER_MEMORY_N_N)(FUNCTION_ARGUMENTS)                                                            \
{                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                       \
    CHECK_SIZE_OF_MEMORY();                                                                                                         \
    if ((sizeOfMemory <= Arg1) && (sizeOfRegisters <= Arg2))                                                                        \
        return false;                                                                                                               \
    return *((castType*)GetElementFromList(Memory, Arg1)) operator *((castType*)GetElementFromList(Registers, Arg2));               \
}                                                                                                                                   \
static bool GLUE(name ##width, _REGISTER_MEMORY_F_N)(FUNCTION_ARGUMENTS)                                                            \
{                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                         \
    if (sizeOfMemory <= Arg1)                                                                                                       \
        return false;                                                                                                               \
    return *((castType*)GetElementFromList(Memory, Arg1)) operator *((castType*)FastGetElementFromList(Registers, Arg2));           \
}                                                                                                                                   \
static bool GLUE(name ##width, _MEMORY_MEMORY_N_N)(FUNCTION_ARGUMENTS)                                                              \
{                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                         \
    if (sizeOfMemory <= ((Arg1 > Arg2) ? Arg1 : Arg2))                                                                              \
        return false;                                                                                                               \
    return *((castType*)GetElementFromList(Memory, Arg1)) operator *((castType*)GetElementFromList(Memory, Arg2));                  \
}                                                                                                                                   \
static bool GLUE(name ##width, _MEMORY_MEMORY_F_N)(FUNCTION_ARGUMENTS)                                                              \
{                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                         \
    if (sizeOfMemory <= Arg1)                                                                                                       \
        return false;                                                                                                               \
    return *((castType*)GetElementFromList(Memory, Arg1)) operator *((castType*)FastGetElementFromList(Memory, Arg2));              \
}                                                                                                                                   \
                                                                                                                                    \
                                                                                                                                    \
                                                                                                                                    \
static bool GLUE(name ##width, _NUM_MEMORY_F)(FUNCTION_ARGUMENTS)                                                                   \
{                                                                                                                                   \
    return *((castType*)FastGetElementFromList(Memory, Arg1)) operator (castType)Arg2;                                              \
}                                                                                                                                   \
static bool GLUE(name ##width, _REGISTER_MEMORY_N_F)(FUNCTION_ARGUMENTS)                                                            \
{                                                                                                                                   \
    CHECK_SIZE_OF_REGISTER();                                                                                                       \
    if (sizeOfRegisters <= Arg2)                                                                                                    \
        return false;                                                                                                               \
    return *((castType*)FastGetElementFromList(Memory, Arg1)) operator *((castType*)GetElementFromList(Registers, Arg2));           \
}                                                                                                                                   \
static bool GLUE(name ##width, _REGISTER_MEMORY_F_F)(FUNCTION_ARGUMENTS)                                                            \
{                                                                                                                                   \
    return *((castType*)FastGetElementFromList(Memory, Arg1)) operator *((castType*)FastGetElementFromList(Registers, Arg2));       \
}                                                                                                                                   \
static bool GLUE(name ##width, _MEMORY_MEMORY_N_F)(FUNCTION_ARGUMENTS)                                                              \
{                                                                                                                                   \
    CHECK_SIZE_OF_MEMORY();                                                                                                         \
    if (sizeOfMemory <= Arg2)                                                                                                       \
        return false;                                                                                                               \
    return *((castType*)FastGetElementFromList(Memory, Arg1)) operator *((castType*)GetElementFromList(Memory, Arg2));              \
}                                                                                                                                   \
static bool GLUE(name ##width, _MEMORY_MEMORY_F_F)(FUNCTION_ARGUMENTS)                                                              \
{                                                                                                                                   \
    return *((castType*)FastGetElementFromList(Memory, Arg1)) operator *((castType*)FastGetElementFromList(Memory, Arg2));          \
}



bool HANDLE_OPCODE_V2(Instruction instruction, uint32_t* poition, CList Memory, CList Registers);

bool MOV_V2(MODE_FUNCTION_ARGUMENTS);
bool ADD_V2(MODE_FUNCTION_ARGUMENTS);
bool SUB_V2(MODE_FUNCTION_ARGUMENTS);
bool MULT_V2(MODE_FUNCTION_ARGUMENTS);
bool DIV_V2(MODE_FUNCTION_ARGUMENTS);
bool MOD_V2(MODE_FUNCTION_ARGUMENTS);
bool LSHIFT_V2(MODE_FUNCTION_ARGUMENTS);
bool RSHIFT_V2(MODE_FUNCTION_ARGUMENTS);
bool AND_V2(MODE_FUNCTION_ARGUMENTS);
bool OR_V2(MODE_FUNCTION_ARGUMENTS);
bool XOR_V2(MODE_FUNCTION_ARGUMENTS);
bool NOT_V2(MODE_FUNCTION_ARGUMENTS);
bool CMPEQ_V2(MODE_FUNCTION_ARGUMENTS);
bool CMPNE_V2(MODE_FUNCTION_ARGUMENTS);
bool CMPLT_V2(MODE_FUNCTION_ARGUMENTS);
bool CMPGT_V2(MODE_FUNCTION_ARGUMENTS);
bool CMPLE_V2(MODE_FUNCTION_ARGUMENTS);
bool CMPGE_V2(MODE_FUNCTION_ARGUMENTS);