#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(RSHIFT, 8, int8_t, >>=)
ASSIGNMENT_FUNCS(RSHIFT, 16, int16_t, >>=)
ASSIGNMENT_FUNCS(RSHIFT, 32, int32_t, >>=)
ASSIGNMENT_FUNCS(RSHIFT, 64, int64_t, >>=)



static bool (*RSHIFT_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    RSHIFT8_NUM_REGISTER_N,                                                // 0b0000010001
    RSHIFT8_REGISTER_REGISTER_N_N,                                         // 0b0000010010
    RSHIFT8_REGISTER_REGISTER_F_N,                                         // 0b0000010011
    RSHIFT8_MEMORY_REGISTER_N_N,                                           // 0b0000010100
    RSHIFT8_MEMORY_REGISTER_F_N,                                           // 0b0000010101
    NULL,
    NULL,
    NULL,
    RSHIFT8_NUM_REGISTER_F,                                                // 0b0000011001
    RSHIFT8_REGISTER_REGISTER_N_F,                                         // 0b0000011010
    RSHIFT8_REGISTER_REGISTER_F_F,                                         // 0b0000011011
    RSHIFT8_MEMORY_REGISTER_N_F,                                           // 0b0000011100
    RSHIFT8_MEMORY_REGISTER_F_F,                                           // 0b0000011101
    NULL,
    NULL,
    NULL,
    RSHIFT8_NUM_MEMORY_N,                                                  // 0b0000100001
    RSHIFT8_REGISTER_MEMORY_N_N,                                           // 0b0000100010
    RSHIFT8_REGISTER_MEMORY_F_N,                                           // 0b0000100011
    RSHIFT8_MEMORY_MEMORY_N_N,                                             // 0b0000100100
    RSHIFT8_MEMORY_MEMORY_F_N,                                             // 0b0000100101
    NULL,
    NULL,
    NULL,
    RSHIFT8_NUM_MEMORY_F,                                                  // 0b0000101001
    RSHIFT8_REGISTER_MEMORY_N_F,                                           // 0b0000101000
    RSHIFT8_REGISTER_MEMORY_F_F,                                           // 0b0000101011
    RSHIFT8_MEMORY_MEMORY_N_F,                                             // 0b0000101100
    RSHIFT8_MEMORY_MEMORY_F_F,                                             // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    RSHIFT16_NUM_REGISTER_N,                                               // 0b0010010001
    RSHIFT16_REGISTER_REGISTER_N_N,                                        // 0b0010010010
    RSHIFT16_REGISTER_REGISTER_F_N,                                        // 0b0010010011
    RSHIFT16_MEMORY_REGISTER_N_N,                                          // 0b0010010100
    RSHIFT16_MEMORY_REGISTER_F_N,                                          // 0b0010010101
    NULL,
    NULL,
    NULL,
    RSHIFT16_NUM_REGISTER_F,                                               // 0b0010011001
    RSHIFT16_REGISTER_REGISTER_N_F,                                        // 0b0010011010
    RSHIFT16_REGISTER_REGISTER_F_F,                                        // 0b0010011011
    RSHIFT16_MEMORY_REGISTER_N_F,                                          // 0b0010011100
    RSHIFT16_MEMORY_REGISTER_F_F,                                          // 0b0010011101
    NULL,
    NULL,
    NULL,
    RSHIFT16_NUM_MEMORY_N,                                                 // 0b0010100001
    RSHIFT16_REGISTER_MEMORY_N_N,                                          // 0b0010100010
    RSHIFT16_REGISTER_MEMORY_F_N,                                          // 0b0010100011
    RSHIFT16_MEMORY_MEMORY_N_N,                                            // 0b0010100100
    RSHIFT16_MEMORY_MEMORY_F_N,                                            // 0b0010100101
    NULL,
    NULL,
    NULL,
    RSHIFT16_NUM_MEMORY_F,                                                 // 0b0010101001
    RSHIFT16_REGISTER_MEMORY_N_F,                                          // 0b0010101000
    RSHIFT16_REGISTER_MEMORY_F_F,                                          // 0b0010101011
    RSHIFT16_MEMORY_MEMORY_N_F,                                            // 0b0010101100
    RSHIFT16_MEMORY_MEMORY_F_F,                                            // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    RSHIFT32_NUM_REGISTER_N,                                               // 0b0100010001
    RSHIFT32_REGISTER_REGISTER_N_N,                                        // 0b0100010010
    RSHIFT32_REGISTER_REGISTER_F_N,                                        // 0b0100010011
    RSHIFT32_MEMORY_REGISTER_N_N,                                          // 0b0100010100
    RSHIFT32_MEMORY_REGISTER_F_N,                                          // 0b0100010101
    NULL,
    NULL,
    NULL,
    RSHIFT32_NUM_REGISTER_F,                                               // 0b0100011001
    RSHIFT32_REGISTER_REGISTER_N_F,                                        // 0b0100011010
    RSHIFT32_REGISTER_REGISTER_F_F,                                        // 0b0100011011
    RSHIFT32_MEMORY_REGISTER_N_F,                                          // 0b0100011100
    RSHIFT32_MEMORY_REGISTER_F_F,                                          // 0b0100011101
    NULL,
    NULL,
    NULL,
    RSHIFT32_NUM_MEMORY_N,                                                 // 0b0100100001
    RSHIFT32_REGISTER_MEMORY_N_N,                                          // 0b0100100010
    RSHIFT32_REGISTER_MEMORY_F_N,                                          // 0b0100100011
    RSHIFT32_MEMORY_MEMORY_N_N,                                            // 0b0100100100
    RSHIFT32_MEMORY_MEMORY_F_N,                                            // 0b0100100101
    NULL,
    NULL,
    NULL,
    RSHIFT32_NUM_MEMORY_F,                                                 // 0b0100101001
    RSHIFT32_REGISTER_MEMORY_N_F,                                          // 0b0100101000
    RSHIFT32_REGISTER_MEMORY_F_F,                                          // 0b0100101011
    RSHIFT32_MEMORY_MEMORY_N_F,                                            // 0b0100101100
    RSHIFT32_MEMORY_MEMORY_F_F,                                            // 0b0100101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    RSHIFT64_NUM_REGISTER_N,                                               // 0b1000010001
    RSHIFT64_REGISTER_REGISTER_N_N,                                        // 0b1000010010
    RSHIFT64_REGISTER_REGISTER_F_N,                                        // 0b1000010011
    RSHIFT64_MEMORY_REGISTER_N_N,                                          // 0b1000010100
    RSHIFT64_MEMORY_REGISTER_F_N,                                          // 0b1000010101
    NULL,
    NULL,
    NULL,
    RSHIFT64_NUM_REGISTER_F,                                               // 0b1000011001
    RSHIFT64_REGISTER_REGISTER_N_F,                                        // 0b1000011010
    RSHIFT64_REGISTER_REGISTER_F_F,                                        // 0b1000011011
    RSHIFT64_MEMORY_REGISTER_N_F,                                          // 0b1000011100
    RSHIFT64_MEMORY_REGISTER_F_F,                                          // 0b1000011101
    NULL,
    NULL,
    NULL,
    RSHIFT64_NUM_MEMORY_N,                                                 // 0b1000100001
    RSHIFT64_REGISTER_MEMORY_N_N,                                          // 0b1000100010
    RSHIFT64_REGISTER_MEMORY_F_N,                                          // 0b1000100011
    RSHIFT64_MEMORY_MEMORY_N_N,                                            // 0b1000100100
    RSHIFT64_MEMORY_MEMORY_F_N,                                            // 0b1000100101
    NULL,
    NULL,
    NULL,
    RSHIFT64_NUM_MEMORY_F,                                                 // 0b1000101001
    RSHIFT64_REGISTER_MEMORY_N_F,                                          // 0b1000101000
    RSHIFT64_REGISTER_MEMORY_F_F,                                          // 0b1000101011
    RSHIFT64_MEMORY_MEMORY_N_F,                                            // 0b1000101100
    RSHIFT64_MEMORY_MEMORY_F_F,                                            // 0b1000101101
};



bool RSHIFT_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (RSHIFT_MODES[Mode]) ? RSHIFT_MODES[Mode](PASS_ARGUMENTS) : false;
}