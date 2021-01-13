#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(DIV, 8, int8_t, /=)
ASSIGNMENT_FUNCS(DIV, 16, int16_t, /=)
ASSIGNMENT_FUNCS(DIV, 32, int32_t, /=)
ASSIGNMENT_FUNCS(DIV, 64, int64_t, /=)



static bool (*DIV_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    DIV8_NUM_REGISTER_N,                                                // 0b0000001010
    DIV8_NUM_REGISTER_F,                                                // 0b0000001011
    DIV8_NUM_MEMORY_N,                                                  // 0b0000001100
    DIV8_NUM_MEMORY_F,                                                  // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV8_REGISTER_REGISTER_N_N,                                         // 0b0000010010
    DIV8_REGISTER_REGISTER_N_F,                                         // 0b0000010011
    DIV8_REGISTER_MEMORY_N_N,                                           // 0b0000010100
    DIV8_REGISTER_MEMORY_N_F,                                           // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV8_REGISTER_REGISTER_F_N,                                         // 0b0000011010
    DIV8_REGISTER_REGISTER_F_F,                                         // 0b0000011011
    DIV8_REGISTER_MEMORY_F_N,                                           // 0b0000011100
    DIV8_REGISTER_MEMORY_F_F,                                           // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV8_MEMORY_REGISTER_N_N,                                           // 0b0000100010
    DIV8_MEMORY_REGISTER_N_F,                                           // 0b0000100011
    DIV8_MEMORY_MEMORY_N_N,                                             // 0b0000100100
    DIV8_MEMORY_MEMORY_N_F,                                             // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV8_MEMORY_REGISTER_F_N,                                           // 0b0000101010
    DIV8_MEMORY_MEMORY_F_F,                                             // 0b0000101011
    DIV8_MEMORY_MEMORY_N_N,                                             // 0b0000101100
    DIV8_MEMORY_MEMORY_F_F,                                             // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    DIV16_NUM_REGISTER_N,                                               // 0b0001001010
    DIV16_NUM_REGISTER_F,                                               // 0b0001001011
    DIV16_NUM_MEMORY_N,                                                 // 0b0001001100
    DIV16_NUM_MEMORY_F,                                                 // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV16_REGISTER_REGISTER_N_N,                                        // 0b0001010010
    DIV16_REGISTER_REGISTER_N_F,                                        // 0b0001010011
    DIV16_REGISTER_MEMORY_N_N,                                          // 0b0001010100
    DIV16_REGISTER_MEMORY_N_F,                                          // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV16_REGISTER_REGISTER_F_N,                                        // 0b0001011010
    DIV16_REGISTER_REGISTER_F_F,                                        // 0b0001011011
    DIV16_REGISTER_MEMORY_F_N,                                          // 0b0001011100
    DIV16_REGISTER_MEMORY_F_F,                                          // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV16_MEMORY_REGISTER_N_N,                                          // 0b0001100010
    DIV16_MEMORY_REGISTER_N_F,                                          // 0b0001100011
    DIV16_MEMORY_MEMORY_N_N,                                            // 0b0001100100
    DIV16_MEMORY_MEMORY_N_F,                                            // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV16_MEMORY_REGISTER_F_N,                                          // 0b0001101010
    DIV16_MEMORY_MEMORY_F_F,                                            // 0b0001101011
    DIV16_MEMORY_MEMORY_N_N,                                            // 0b0001101100
    DIV16_MEMORY_MEMORY_F_F,                                            // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    DIV32_NUM_REGISTER_N,                                               // 0b0010001010
    DIV32_NUM_REGISTER_F,                                               // 0b0010001011
    DIV32_NUM_MEMORY_N,                                                 // 0b0010001100
    DIV32_NUM_MEMORY_F,                                                 // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV32_REGISTER_REGISTER_N_N,                                        // 0b0010010010
    DIV32_REGISTER_REGISTER_N_F,                                        // 0b0010010011
    DIV32_REGISTER_MEMORY_N_N,                                          // 0b0010010100
    DIV32_REGISTER_MEMORY_N_F,                                          // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV32_REGISTER_REGISTER_F_N,                                        // 0b0010011010
    DIV32_REGISTER_REGISTER_F_F,                                        // 0b0010011011
    DIV32_REGISTER_MEMORY_F_N,                                          // 0b0010011100
    DIV32_REGISTER_MEMORY_F_F,                                          // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV32_MEMORY_REGISTER_N_N,                                          // 0b0010100010
    DIV32_MEMORY_REGISTER_N_F,                                          // 0b0010100011
    DIV32_MEMORY_MEMORY_N_N,                                            // 0b0010100100
    DIV32_MEMORY_MEMORY_N_F,                                            // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV32_MEMORY_REGISTER_F_N,                                          // 0b0010101010
    DIV32_MEMORY_MEMORY_F_F,                                            // 0b0010101011
    DIV32_MEMORY_MEMORY_N_N,                                            // 0b0010101100
    DIV32_MEMORY_MEMORY_F_F,                                            // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    DIV64_NUM_REGISTER_N,                                               // 0b0100001010
    DIV64_NUM_REGISTER_F,                                               // 0b0100001011
    DIV64_NUM_MEMORY_N,                                                 // 0b0100001100
    DIV64_NUM_MEMORY_F,                                                 // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV64_REGISTER_REGISTER_N_N,                                        // 0b0100010010
    DIV64_REGISTER_REGISTER_N_F,                                        // 0b0100010011
    DIV64_REGISTER_MEMORY_N_N,                                          // 0b0100010100
    DIV64_REGISTER_MEMORY_N_F,                                          // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV64_REGISTER_REGISTER_F_N,                                        // 0b0100011010
    DIV64_REGISTER_REGISTER_F_F,                                        // 0b0100011011
    DIV64_REGISTER_MEMORY_F_N,                                          // 0b0100011100
    DIV64_REGISTER_MEMORY_F_F,                                          // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV64_MEMORY_REGISTER_N_N,                                          // 0b0100100010
    DIV64_MEMORY_REGISTER_N_F,                                          // 0b0100100011
    DIV64_MEMORY_MEMORY_N_N,                                            // 0b0100100100
    DIV64_MEMORY_MEMORY_N_F,                                            // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    DIV64_MEMORY_REGISTER_F_N,                                          // 0b0100101010
    DIV64_MEMORY_MEMORY_F_F,                                            // 0b0100101011
    DIV64_MEMORY_MEMORY_N_N,                                            // 0b0100101100
    DIV64_MEMORY_MEMORY_F_F,                                            // 0b0100101101
};



bool DIV_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (DIV_MODES[Mode]) ? DIV_MODES[Mode](PASS_ARGUMENTS) : false;
}