#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



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
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOD8_NUM_REGISTER_N,                                                // 0b0000010001
    MOD8_REGISTER_REGISTER_N_N,                                         // 0b0000010010
    MOD8_REGISTER_REGISTER_F_N,                                         // 0b0000010011
    MOD8_MEMORY_REGISTER_N_N,                                           // 0b0000010100
    MOD8_MEMORY_REGISTER_F_N,                                           // 0b0000010101
    NULL,
    NULL,
    NULL,
    MOD8_NUM_REGISTER_F,                                                // 0b0000011001
    MOD8_REGISTER_REGISTER_N_F,                                         // 0b0000011010
    MOD8_REGISTER_REGISTER_F_F,                                         // 0b0000011011
    MOD8_MEMORY_REGISTER_N_F,                                           // 0b0000011100
    MOD8_MEMORY_REGISTER_F_F,                                           // 0b0000011101
    NULL,
    NULL,
    NULL,
    MOD8_NUM_MEMORY_N,                                                  // 0b0000100001
    MOD8_REGISTER_MEMORY_N_N,                                           // 0b0000100010
    MOD8_REGISTER_MEMORY_F_N,                                           // 0b0000100011
    MOD8_MEMORY_MEMORY_N_N,                                             // 0b0000100100
    MOD8_MEMORY_MEMORY_F_N,                                             // 0b0000100101
    NULL,
    NULL,
    NULL,
    MOD8_NUM_MEMORY_F,                                                  // 0b0000101001
    MOD8_REGISTER_MEMORY_N_F,                                           // 0b0000101000
    MOD8_REGISTER_MEMORY_F_F,                                           // 0b0000101011
    MOD8_MEMORY_MEMORY_N_F,                                             // 0b0000101100
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
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOD16_NUM_REGISTER_N,                                               // 0b0010010001
    MOD16_REGISTER_REGISTER_N_N,                                        // 0b0010010010
    MOD16_REGISTER_REGISTER_F_N,                                        // 0b0010010011
    MOD16_MEMORY_REGISTER_N_N,                                          // 0b0010010100
    MOD16_MEMORY_REGISTER_F_N,                                          // 0b0010010101
    NULL,
    NULL,
    NULL,
    MOD16_NUM_REGISTER_F,                                               // 0b0010011001
    MOD16_REGISTER_REGISTER_N_F,                                        // 0b0010011010
    MOD16_REGISTER_REGISTER_F_F,                                        // 0b0010011011
    MOD16_MEMORY_REGISTER_N_F,                                          // 0b0010011100
    MOD16_MEMORY_REGISTER_F_F,                                          // 0b0010011101
    NULL,
    NULL,
    NULL,
    MOD16_NUM_MEMORY_N,                                                 // 0b0010100001
    MOD16_REGISTER_MEMORY_N_N,                                          // 0b0010100010
    MOD16_REGISTER_MEMORY_F_N,                                          // 0b0010100011
    MOD16_MEMORY_MEMORY_N_N,                                            // 0b0010100100
    MOD16_MEMORY_MEMORY_F_N,                                            // 0b0010100101
    NULL,
    NULL,
    NULL,
    MOD16_NUM_MEMORY_F,                                                 // 0b0010101001
    MOD16_REGISTER_MEMORY_N_F,                                          // 0b0010101000
    MOD16_REGISTER_MEMORY_F_F,                                          // 0b0010101011
    MOD16_MEMORY_MEMORY_N_F,                                            // 0b0010101100
    MOD16_MEMORY_MEMORY_F_F,                                            // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOD32_NUM_REGISTER_N,                                               // 0b0100010001
    MOD32_REGISTER_REGISTER_N_N,                                        // 0b0100010010
    MOD32_REGISTER_REGISTER_F_N,                                        // 0b0100010011
    MOD32_MEMORY_REGISTER_N_N,                                          // 0b0100010100
    MOD32_MEMORY_REGISTER_F_N,                                          // 0b0100010101
    NULL,
    NULL,
    NULL,
    MOD32_NUM_REGISTER_F,                                               // 0b0100011001
    MOD32_REGISTER_REGISTER_N_F,                                        // 0b0100011010
    MOD32_REGISTER_REGISTER_F_F,                                        // 0b0100011011
    MOD32_MEMORY_REGISTER_N_F,                                          // 0b0100011100
    MOD32_MEMORY_REGISTER_F_F,                                          // 0b0100011101
    NULL,
    NULL,
    NULL,
    MOD32_NUM_MEMORY_N,                                                 // 0b0100100001
    MOD32_REGISTER_MEMORY_N_N,                                          // 0b0100100010
    MOD32_REGISTER_MEMORY_F_N,                                          // 0b0100100011
    MOD32_MEMORY_MEMORY_N_N,                                            // 0b0100100100
    MOD32_MEMORY_MEMORY_F_N,                                            // 0b0100100101
    NULL,
    NULL,
    NULL,
    MOD32_NUM_MEMORY_F,                                                 // 0b0100101001
    MOD32_REGISTER_MEMORY_N_F,                                          // 0b0100101000
    MOD32_REGISTER_MEMORY_F_F,                                          // 0b0100101011
    MOD32_MEMORY_MEMORY_N_F,                                            // 0b0100101100
    MOD32_MEMORY_MEMORY_F_F,                                            // 0b0100101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOD64_NUM_REGISTER_N,                                               // 0b1000010001
    MOD64_REGISTER_REGISTER_N_N,                                        // 0b1000010010
    MOD64_REGISTER_REGISTER_F_N,                                        // 0b1000010011
    MOD64_MEMORY_REGISTER_N_N,                                          // 0b1000010100
    MOD64_MEMORY_REGISTER_F_N,                                          // 0b1000010101
    NULL,
    NULL,
    NULL,
    MOD64_NUM_REGISTER_F,                                               // 0b1000011001
    MOD64_REGISTER_REGISTER_N_F,                                        // 0b1000011010
    MOD64_REGISTER_REGISTER_F_F,                                        // 0b1000011011
    MOD64_MEMORY_REGISTER_N_F,                                          // 0b1000011100
    MOD64_MEMORY_REGISTER_F_F,                                          // 0b1000011101
    NULL,
    NULL,
    NULL,
    MOD64_NUM_MEMORY_N,                                                 // 0b1000100001
    MOD64_REGISTER_MEMORY_N_N,                                          // 0b1000100010
    MOD64_REGISTER_MEMORY_F_N,                                          // 0b1000100011
    MOD64_MEMORY_MEMORY_N_N,                                            // 0b1000100100
    MOD64_MEMORY_MEMORY_F_N,                                            // 0b1000100101
    NULL,
    NULL,
    NULL,
    MOD64_NUM_MEMORY_F,                                                 // 0b1000101001
    MOD64_REGISTER_MEMORY_N_F,                                          // 0b1000101000
    MOD64_REGISTER_MEMORY_F_F,                                          // 0b1000101011
    MOD64_MEMORY_MEMORY_N_F,                                            // 0b1000101100
    MOD64_MEMORY_MEMORY_F_F,                                            // 0b1000101101
};



bool MOD_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (MOD_MODES[Mode]) ? MOD_MODES[Mode](PASS_ARGUMENTS) : false;
}