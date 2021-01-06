#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(LSHIFT, 8, int8_t, <<=)
ASSIGNMENT_FUNCS(LSHIFT, 16, int16_t, <<=)
ASSIGNMENT_FUNCS(LSHIFT, 32, int32_t, <<=)
ASSIGNMENT_FUNCS(LSHIFT, 64, int64_t, <<=)



static bool (*LSHIFT_MODES[])(ARGUMENT_TYPES) = {
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
    LSHIFT8_NUM_REGISTER_N,                                             // 0b0000001010
    LSHIFT8_NUM_REGISTER_F,                                             // 0b0000001011
    LSHIFT8_NUM_MEMORY_N,                                               // 0b0000001100
    LSHIFT8_NUM_MEMORY_F,                                               // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT8_REGISTER_REGISTER_N_N,                                      // 0b0000010010
    LSHIFT8_REGISTER_REGISTER_N_F,                                      // 0b0000010011
    LSHIFT8_REGISTER_MEMORY_N_N,                                        // 0b0000010100
    LSHIFT8_REGISTER_MEMORY_N_F,                                        // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT8_REGISTER_REGISTER_F_N,                                      // 0b0000011010
    LSHIFT8_REGISTER_REGISTER_F_F,                                      // 0b0000011011
    LSHIFT8_REGISTER_MEMORY_F_N,                                        // 0b0000011100
    LSHIFT8_REGISTER_MEMORY_F_F,                                        // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT8_MEMORY_REGISTER_N_N,                                        // 0b0000100010
    LSHIFT8_MEMORY_REGISTER_N_F,                                        // 0b0000100011
    LSHIFT8_MEMORY_MEMORY_N_N,                                          // 0b0000100100
    LSHIFT8_MEMORY_MEMORY_N_F,                                          // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT8_MEMORY_REGISTER_F_N,                                        // 0b0000101010
    LSHIFT8_MEMORY_MEMORY_F_F,                                          // 0b0000101011
    LSHIFT8_MEMORY_MEMORY_N_N,                                          // 0b0000101100
    LSHIFT8_MEMORY_MEMORY_F_F,                                          // 0b0000101101
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
    LSHIFT16_NUM_REGISTER_N,                                            // 0b0001001010
    LSHIFT16_NUM_REGISTER_F,                                            // 0b0001001011
    LSHIFT16_NUM_MEMORY_N,                                              // 0b0001001100
    LSHIFT16_NUM_MEMORY_F,                                              // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT16_REGISTER_REGISTER_N_N,                                     // 0b0001010010
    LSHIFT16_REGISTER_REGISTER_N_F,                                     // 0b0001010011
    LSHIFT16_REGISTER_MEMORY_N_N,                                       // 0b0001010100
    LSHIFT16_REGISTER_MEMORY_N_F,                                       // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT16_REGISTER_REGISTER_F_N,                                     // 0b0001011010
    LSHIFT16_REGISTER_REGISTER_F_F,                                     // 0b0001011011
    LSHIFT16_REGISTER_MEMORY_F_N,                                       // 0b0001011100
    LSHIFT16_REGISTER_MEMORY_F_F,                                       // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT16_MEMORY_REGISTER_N_N,                                       // 0b0001100010
    LSHIFT16_MEMORY_REGISTER_N_F,                                       // 0b0001100011
    LSHIFT16_MEMORY_MEMORY_N_N,                                         // 0b0001100100
    LSHIFT16_MEMORY_MEMORY_N_F,                                         // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT16_MEMORY_REGISTER_F_N,                                       // 0b0001101010
    LSHIFT16_MEMORY_MEMORY_F_F,                                         // 0b0001101011
    LSHIFT16_MEMORY_MEMORY_N_N,                                         // 0b0001101100
    LSHIFT16_MEMORY_MEMORY_F_F,                                         // 0b0001101101
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
    LSHIFT32_NUM_REGISTER_N,                                            // 0b0010001010
    LSHIFT32_NUM_REGISTER_F,                                            // 0b0010001011
    LSHIFT32_NUM_MEMORY_N,                                              // 0b0010001100
    LSHIFT32_NUM_MEMORY_F,                                              // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT32_REGISTER_REGISTER_N_N,                                     // 0b0010010010
    LSHIFT32_REGISTER_REGISTER_N_F,                                     // 0b0010010011
    LSHIFT32_REGISTER_MEMORY_N_N,                                       // 0b0010010100
    LSHIFT32_REGISTER_MEMORY_N_F,                                       // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT32_REGISTER_REGISTER_F_N,                                     // 0b0010011010
    LSHIFT32_REGISTER_REGISTER_F_F,                                     // 0b0010011011
    LSHIFT32_REGISTER_MEMORY_F_N,                                       // 0b0010011100
    LSHIFT32_REGISTER_MEMORY_F_F,                                       // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT32_MEMORY_REGISTER_N_N,                                       // 0b0010100010
    LSHIFT32_MEMORY_REGISTER_N_F,                                       // 0b0010100011
    LSHIFT32_MEMORY_MEMORY_N_N,                                         // 0b0010100100
    LSHIFT32_MEMORY_MEMORY_N_F,                                         // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT32_MEMORY_REGISTER_F_N,                                       // 0b0010101010
    LSHIFT32_MEMORY_MEMORY_F_F,                                         // 0b0010101011
    LSHIFT32_MEMORY_MEMORY_N_N,                                         // 0b0010101100
    LSHIFT32_MEMORY_MEMORY_F_F,                                         // 0b0010101101
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
    LSHIFT64_NUM_REGISTER_N,                                            // 0b0100001010
    LSHIFT64_NUM_REGISTER_F,                                            // 0b0100001011
    LSHIFT64_NUM_MEMORY_N,                                              // 0b0100001100
    LSHIFT64_NUM_MEMORY_F,                                              // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT64_REGISTER_REGISTER_N_N,                                     // 0b0100010010
    LSHIFT64_REGISTER_REGISTER_N_F,                                     // 0b0100010011
    LSHIFT64_REGISTER_MEMORY_N_N,                                       // 0b0100010100
    LSHIFT64_REGISTER_MEMORY_N_F,                                       // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT64_REGISTER_REGISTER_F_N,                                     // 0b0100011010
    LSHIFT64_REGISTER_REGISTER_F_F,                                     // 0b0100011011
    LSHIFT64_REGISTER_MEMORY_F_N,                                       // 0b0100011100
    LSHIFT64_REGISTER_MEMORY_F_F,                                       // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT64_MEMORY_REGISTER_N_N,                                       // 0b0100100010
    LSHIFT64_MEMORY_REGISTER_N_F,                                       // 0b0100100011
    LSHIFT64_MEMORY_MEMORY_N_N,                                         // 0b0100100100
    LSHIFT64_MEMORY_MEMORY_N_F,                                         // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    LSHIFT64_MEMORY_REGISTER_F_N,                                       // 0b0100101010
    LSHIFT64_MEMORY_MEMORY_F_F,                                         // 0b0100101011
    LSHIFT64_MEMORY_MEMORY_N_N,                                         // 0b0100101100
    LSHIFT64_MEMORY_MEMORY_F_F,                                         // 0b0100101101
};



bool LSHIFT_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (LSHIFT_MODES[Mode]) ? LSHIFT_MODES[Mode](PASS_ARGUMENTS) : false;
}