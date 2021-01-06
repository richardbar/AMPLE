#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)


COMPARISON_FUNCS(EQ, 8, int8_t, ==)
COMPARISON_FUNCS(EQ, 16, int16_t, ==)
COMPARISON_FUNCS(EQ, 32, int32_t, ==)
COMPARISON_FUNCS(EQ, 64, int64_t, ==)



static bool (*CMPEQ_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ8_NUM_REGISTER_N,                                              // 0b0000001010
    CMPEQ8_NUM_REGISTER_F,                                              // 0b0000001011
    CMPEQ8_NUM_MEMORY_N,                                                // 0b0000001100
    CMPEQ8_NUM_MEMORY_F,                                                // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ8_REGISTER_REGISTER_N_N,                                       // 0b0000010010
    CMPEQ8_REGISTER_REGISTER_N_F,                                       // 0b0000010011
    CMPEQ8_REGISTER_MEMORY_N_N,                                         // 0b0000010100
    CMPEQ8_REGISTER_MEMORY_N_F,                                         // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ8_REGISTER_REGISTER_F_N,                                       // 0b0000011010
    CMPEQ8_REGISTER_REGISTER_F_F,                                       // 0b0000011011
    CMPEQ8_REGISTER_MEMORY_F_N,                                         // 0b0000011100
    CMPEQ8_REGISTER_MEMORY_F_F,                                         // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ8_MEMORY_REGISTER_N_N,                                         // 0b0000100010
    CMPEQ8_MEMORY_REGISTER_N_F,                                         // 0b0000100011
    CMPEQ8_MEMORY_MEMORY_N_N,                                           // 0b0000100100
    CMPEQ8_MEMORY_MEMORY_N_F,                                           // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ8_MEMORY_REGISTER_F_N,                                         // 0b0000101010
    CMPEQ8_MEMORY_MEMORY_F_F,                                           // 0b0000101011
    CMPEQ8_MEMORY_MEMORY_N_N,                                           // 0b0000101100
    CMPEQ8_MEMORY_MEMORY_F_F,                                           // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ16_NUM_REGISTER_N,                                             // 0b0001001010
    CMPEQ16_NUM_REGISTER_F,                                             // 0b0001001011
    CMPEQ16_NUM_MEMORY_N,                                               // 0b0001001100
    CMPEQ16_NUM_MEMORY_F,                                               // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ16_REGISTER_REGISTER_N_N,                                      // 0b0001010010
    CMPEQ16_REGISTER_REGISTER_N_F,                                      // 0b0001010011
    CMPEQ16_REGISTER_MEMORY_N_N,                                        // 0b0001010100
    CMPEQ16_REGISTER_MEMORY_N_F,                                        // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ16_REGISTER_REGISTER_F_N,                                      // 0b0001011010
    CMPEQ16_REGISTER_REGISTER_F_F,                                      // 0b0001011011
    CMPEQ16_REGISTER_MEMORY_F_N,                                        // 0b0001011100
    CMPEQ16_REGISTER_MEMORY_F_F,                                        // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ16_MEMORY_REGISTER_N_N,                                        // 0b0001100010
    CMPEQ16_MEMORY_REGISTER_N_F,                                        // 0b0001100011
    CMPEQ16_MEMORY_MEMORY_N_N,                                          // 0b0001100100
    CMPEQ16_MEMORY_MEMORY_N_F,                                          // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ16_MEMORY_REGISTER_F_N,                                        // 0b0001101010
    CMPEQ16_MEMORY_MEMORY_F_F,                                          // 0b0001101011
    CMPEQ16_MEMORY_MEMORY_N_N,                                          // 0b0001101100
    CMPEQ16_MEMORY_MEMORY_F_F,                                          // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ32_NUM_REGISTER_N,                                             // 0b0010001010
    CMPEQ32_NUM_REGISTER_F,                                             // 0b0010001011
    CMPEQ32_NUM_MEMORY_N,                                               // 0b0010001100
    CMPEQ32_NUM_MEMORY_F,                                               // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ32_REGISTER_REGISTER_N_N,                                      // 0b0010010010
    CMPEQ32_REGISTER_REGISTER_N_F,                                      // 0b0010010011
    CMPEQ32_REGISTER_MEMORY_N_N,                                        // 0b0010010100
    CMPEQ32_REGISTER_MEMORY_N_F,                                        // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ32_REGISTER_REGISTER_F_N,                                      // 0b0010011010
    CMPEQ32_REGISTER_REGISTER_F_F,                                      // 0b0010011011
    CMPEQ32_REGISTER_MEMORY_F_N,                                        // 0b0010011100
    CMPEQ32_REGISTER_MEMORY_F_F,                                        // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ32_MEMORY_REGISTER_N_N,                                        // 0b0010100010
    CMPEQ32_MEMORY_REGISTER_N_F,                                        // 0b0010100011
    CMPEQ32_MEMORY_MEMORY_N_N,                                          // 0b0010100100
    CMPEQ32_MEMORY_MEMORY_N_F,                                          // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ32_MEMORY_REGISTER_F_N,                                        // 0b0010101010
    CMPEQ32_MEMORY_MEMORY_F_F,                                          // 0b0010101011
    CMPEQ32_MEMORY_MEMORY_N_N,                                          // 0b0010101100
    CMPEQ32_MEMORY_MEMORY_F_F,                                          // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ64_NUM_REGISTER_N,                                             // 0b0100001010
    CMPEQ64_NUM_REGISTER_F,                                             // 0b0100001011
    CMPEQ64_NUM_MEMORY_N,                                               // 0b0100001100
    CMPEQ64_NUM_MEMORY_F,                                               // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ64_REGISTER_REGISTER_N_N,                                      // 0b0100010010
    CMPEQ64_REGISTER_REGISTER_N_F,                                      // 0b0100010011
    CMPEQ64_REGISTER_MEMORY_N_N,                                        // 0b0100010100
    CMPEQ64_REGISTER_MEMORY_N_F,                                        // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ64_REGISTER_REGISTER_F_N,                                      // 0b0100011010
    CMPEQ64_REGISTER_REGISTER_F_F,                                      // 0b0100011011
    CMPEQ64_REGISTER_MEMORY_F_N,                                        // 0b0100011100
    CMPEQ64_REGISTER_MEMORY_F_F,                                        // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ64_MEMORY_REGISTER_N_N,                                        // 0b0100100010
    CMPEQ64_MEMORY_REGISTER_N_F,                                        // 0b0100100011
    CMPEQ64_MEMORY_MEMORY_N_N,                                          // 0b0100100100
    CMPEQ64_MEMORY_MEMORY_N_F,                                          // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPEQ64_MEMORY_REGISTER_F_N,                                        // 0b0100101010
    CMPEQ64_MEMORY_MEMORY_F_F,                                          // 0b0100101011
    CMPEQ64_MEMORY_MEMORY_N_N,                                          // 0b0100101100
    CMPEQ64_MEMORY_MEMORY_F_F,                                          // 0b0100101101
};



bool CMPEQ_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (CMPEQ_MODES[Mode]) ? CMPEQ_MODES[Mode](PASS_ARGUMENTS) : false;
}