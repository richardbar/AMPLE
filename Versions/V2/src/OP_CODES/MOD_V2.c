#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(MOD, 8, int8_t, %=)
ASSIGNMENT_FUNCS(MOD, 16, int16_t, %=)
ASSIGNMENT_FUNCS(MOD, 32, int32_t, %=)
ASSIGNMENT_FUNCS(MOD, 64, int64_t, %=)



static bool (*MOD_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOD8_NUM_REGISTER_N,                                                // 0b0000001010
    MOD8_NUM_REGISTER_F,                                                // 0b0000001011
    MOD8_NUM_MEMORY_N,                                                  // 0b0000001100
    MOD8_NUM_MEMORY_F,                                                  // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD8_REGISTER_REGISTER_N_N,                                         // 0b0000010010
    MOD8_REGISTER_REGISTER_N_F,                                         // 0b0000010011
    MOD8_REGISTER_MEMORY_N_N,                                           // 0b0000010100
    MOD8_REGISTER_MEMORY_N_F,                                           // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD8_REGISTER_REGISTER_F_N,                                         // 0b0000011010
    MOD8_REGISTER_REGISTER_F_F,                                         // 0b0000011011
    MOD8_REGISTER_MEMORY_F_N,                                           // 0b0000011100
    MOD8_REGISTER_MEMORY_F_F,                                           // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD8_MEMORY_REGISTER_N_N,                                           // 0b0000100010
    MOD8_MEMORY_REGISTER_N_F,                                           // 0b0000100011
    MOD8_MEMORY_MEMORY_N_N,                                             // 0b0000100100
    MOD8_MEMORY_MEMORY_N_F,                                             // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD8_MEMORY_REGISTER_F_N,                                           // 0b0000101010
    MOD8_MEMORY_MEMORY_F_F,                                             // 0b0000101011
    MOD8_MEMORY_MEMORY_N_N,                                             // 0b0000101100
    MOD8_MEMORY_MEMORY_F_F,                                             // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOD16_NUM_REGISTER_N,                                               // 0b0001001010
    MOD16_NUM_REGISTER_F,                                               // 0b0001001011
    MOD16_NUM_MEMORY_N,                                                 // 0b0001001100
    MOD16_NUM_MEMORY_F,                                                 // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD16_REGISTER_REGISTER_N_N,                                        // 0b0001010010
    MOD16_REGISTER_REGISTER_N_F,                                        // 0b0001010011
    MOD16_REGISTER_MEMORY_N_N,                                          // 0b0001010100
    MOD16_REGISTER_MEMORY_N_F,                                          // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD16_REGISTER_REGISTER_F_N,                                        // 0b0001011010
    MOD16_REGISTER_REGISTER_F_F,                                        // 0b0001011011
    MOD16_REGISTER_MEMORY_F_N,                                          // 0b0001011100
    MOD16_REGISTER_MEMORY_F_F,                                          // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD16_MEMORY_REGISTER_N_N,                                          // 0b0001100010
    MOD16_MEMORY_REGISTER_N_F,                                          // 0b0001100011
    MOD16_MEMORY_MEMORY_N_N,                                            // 0b0001100100
    MOD16_MEMORY_MEMORY_N_F,                                            // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD16_MEMORY_REGISTER_F_N,                                          // 0b0001101010
    MOD16_MEMORY_MEMORY_F_F,                                            // 0b0001101011
    MOD16_MEMORY_MEMORY_N_N,                                            // 0b0001101100
    MOD16_MEMORY_MEMORY_F_F,                                            // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOD32_NUM_REGISTER_N,                                               // 0b0010001010
    MOD32_NUM_REGISTER_F,                                               // 0b0010001011
    MOD32_NUM_MEMORY_N,                                                 // 0b0010001100
    MOD32_NUM_MEMORY_F,                                                 // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD32_REGISTER_REGISTER_N_N,                                        // 0b0010010010
    MOD32_REGISTER_REGISTER_N_F,                                        // 0b0010010011
    MOD32_REGISTER_MEMORY_N_N,                                          // 0b0010010100
    MOD32_REGISTER_MEMORY_N_F,                                          // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD32_REGISTER_REGISTER_F_N,                                        // 0b0010011010
    MOD32_REGISTER_REGISTER_F_F,                                        // 0b0010011011
    MOD32_REGISTER_MEMORY_F_N,                                          // 0b0010011100
    MOD32_REGISTER_MEMORY_F_F,                                          // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD32_MEMORY_REGISTER_N_N,                                          // 0b0010100010
    MOD32_MEMORY_REGISTER_N_F,                                          // 0b0010100011
    MOD32_MEMORY_MEMORY_N_N,                                            // 0b0010100100
    MOD32_MEMORY_MEMORY_N_F,                                            // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD32_MEMORY_REGISTER_F_N,                                          // 0b0010101010
    MOD32_MEMORY_MEMORY_F_F,                                            // 0b0010101011
    MOD32_MEMORY_MEMORY_N_N,                                            // 0b0010101100
    MOD32_MEMORY_MEMORY_F_F,                                            // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOD64_NUM_REGISTER_N,                                               // 0b0100001010
    MOD64_NUM_REGISTER_F,                                               // 0b0100001011
    MOD64_NUM_MEMORY_N,                                                 // 0b0100001100
    MOD64_NUM_MEMORY_F,                                                 // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD64_REGISTER_REGISTER_N_N,                                        // 0b0100010010
    MOD64_REGISTER_REGISTER_N_F,                                        // 0b0100010011
    MOD64_REGISTER_MEMORY_N_N,                                          // 0b0100010100
    MOD64_REGISTER_MEMORY_N_F,                                          // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD64_REGISTER_REGISTER_F_N,                                        // 0b0100011010
    MOD64_REGISTER_REGISTER_F_F,                                        // 0b0100011011
    MOD64_REGISTER_MEMORY_F_N,                                          // 0b0100011100
    MOD64_REGISTER_MEMORY_F_F,                                          // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD64_MEMORY_REGISTER_N_N,                                          // 0b0100100010
    MOD64_MEMORY_REGISTER_N_F,                                          // 0b0100100011
    MOD64_MEMORY_MEMORY_N_N,                                            // 0b0100100100
    MOD64_MEMORY_MEMORY_N_F,                                            // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    MOD64_MEMORY_REGISTER_F_N,                                          // 0b0100101010
    MOD64_MEMORY_MEMORY_F_F,                                            // 0b0100101011
    MOD64_MEMORY_MEMORY_N_N,                                            // 0b0100101100
    MOD64_MEMORY_MEMORY_F_F,                                            // 0b0100101101
};



bool MOD_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (MOD_MODES[Mode]) ? MOD_MODES[Mode](PASS_ARGUMENTS) : false;
}