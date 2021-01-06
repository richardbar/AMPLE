#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(MOV, 8, int8_t, =)
ASSIGNMENT_FUNCS(MOV, 16, int16_t, =)
ASSIGNMENT_FUNCS(MOV, 32, int32_t, =)
ASSIGNMENT_FUNCS(MOV, 64, int64_t, =)



static bool (*MOV_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOV8_NUM_REGISTER_N,                                                // 0b0000001010
    MOV8_NUM_REGISTER_F,                                                // 0b0000001011
    MOV8_NUM_MEMORY_N,                                                  // 0b0000001100
    MOV8_NUM_MEMORY_F,                                                  // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV8_REGISTER_REGISTER_N_N,                                         // 0b0000010010
    MOV8_REGISTER_REGISTER_N_F,                                         // 0b0000010011
    MOV8_REGISTER_MEMORY_N_N,                                           // 0b0000010100
    MOV8_REGISTER_MEMORY_N_F,                                           // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV8_REGISTER_REGISTER_F_N,                                         // 0b0000011010
    MOV8_REGISTER_REGISTER_F_F,                                         // 0b0000011011
    MOV8_REGISTER_MEMORY_F_N,                                           // 0b0000011100
    MOV8_REGISTER_MEMORY_F_F,                                           // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV8_MEMORY_REGISTER_N_N,                                           // 0b0000100010
    MOV8_MEMORY_REGISTER_N_F,                                           // 0b0000100011
    MOV8_MEMORY_MEMORY_N_N,                                             // 0b0000100100
    MOV8_MEMORY_MEMORY_N_F,                                             // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV8_MEMORY_REGISTER_F_N,                                           // 0b0000101010
    MOV8_MEMORY_MEMORY_F_F,                                             // 0b0000101011
    MOV8_MEMORY_MEMORY_N_N,                                             // 0b0000101100
    MOV8_MEMORY_MEMORY_F_F,                                             // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOV16_NUM_REGISTER_N,                                               // 0b0001001010
    MOV16_NUM_REGISTER_F,                                               // 0b0001001011
    MOV16_NUM_MEMORY_N,                                                 // 0b0001001100
    MOV16_NUM_MEMORY_F,                                                 // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV16_REGISTER_REGISTER_N_N,                                        // 0b0001010010
    MOV16_REGISTER_REGISTER_N_F,                                        // 0b0001010011
    MOV16_REGISTER_MEMORY_N_N,                                          // 0b0001010100
    MOV16_REGISTER_MEMORY_N_F,                                          // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV16_REGISTER_REGISTER_F_N,                                        // 0b0001011010
    MOV16_REGISTER_REGISTER_F_F,                                        // 0b0001011011
    MOV16_REGISTER_MEMORY_F_N,                                          // 0b0001011100
    MOV16_REGISTER_MEMORY_F_F,                                          // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV16_MEMORY_REGISTER_N_N,                                          // 0b0001100010
    MOV16_MEMORY_REGISTER_N_F,                                          // 0b0001100011
    MOV16_MEMORY_MEMORY_N_N,                                            // 0b0001100100
    MOV16_MEMORY_MEMORY_N_F,                                            // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV16_MEMORY_REGISTER_F_N,                                          // 0b0001101010
    MOV16_MEMORY_MEMORY_F_F,                                            // 0b0001101011
    MOV16_MEMORY_MEMORY_N_N,                                            // 0b0001101100
    MOV16_MEMORY_MEMORY_F_F,                                            // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOV32_NUM_REGISTER_N,                                               // 0b0010001010
    MOV32_NUM_REGISTER_F,                                               // 0b0010001011
    MOV32_NUM_MEMORY_N,                                                 // 0b0010001100
    MOV32_NUM_MEMORY_F,                                                 // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV32_REGISTER_REGISTER_N_N,                                        // 0b0010010010
    MOV32_REGISTER_REGISTER_N_F,                                        // 0b0010010011
    MOV32_REGISTER_MEMORY_N_N,                                          // 0b0010010100
    MOV32_REGISTER_MEMORY_N_F,                                          // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV32_REGISTER_REGISTER_F_N,                                        // 0b0010011010
    MOV32_REGISTER_REGISTER_F_F,                                        // 0b0010011011
    MOV32_REGISTER_MEMORY_F_N,                                          // 0b0010011100
    MOV32_REGISTER_MEMORY_F_F,                                          // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV32_MEMORY_REGISTER_N_N,                                          // 0b0010100010
    MOV32_MEMORY_REGISTER_N_F,                                          // 0b0010100011
    MOV32_MEMORY_MEMORY_N_N,                                            // 0b0010100100
    MOV32_MEMORY_MEMORY_N_F,                                            // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV32_MEMORY_REGISTER_F_N,                                          // 0b0010101010
    MOV32_MEMORY_MEMORY_F_F,                                            // 0b0010101011
    MOV32_MEMORY_MEMORY_N_N,                                            // 0b0010101100
    MOV32_MEMORY_MEMORY_F_F,                                            // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MOV64_NUM_REGISTER_N,                                               // 0b0100001010
    MOV64_NUM_REGISTER_F,                                               // 0b0100001011
    MOV64_NUM_MEMORY_N,                                                 // 0b0100001100
    MOV64_NUM_MEMORY_F,                                                 // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV64_REGISTER_REGISTER_N_N,                                        // 0b0100010010
    MOV64_REGISTER_REGISTER_N_F,                                        // 0b0100010011
    MOV64_REGISTER_MEMORY_N_N,                                          // 0b0100010100
    MOV64_REGISTER_MEMORY_N_F,                                          // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV64_REGISTER_REGISTER_F_N,                                        // 0b0100011010
    MOV64_REGISTER_REGISTER_F_F,                                        // 0b0100011011
    MOV64_REGISTER_MEMORY_F_N,                                          // 0b0100011100
    MOV64_REGISTER_MEMORY_F_F,                                          // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV64_MEMORY_REGISTER_N_N,                                          // 0b0100100010
    MOV64_MEMORY_REGISTER_N_F,                                          // 0b0100100011
    MOV64_MEMORY_MEMORY_N_N,                                            // 0b0100100100
    MOV64_MEMORY_MEMORY_N_F,                                            // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    MOV64_MEMORY_REGISTER_F_N,                                          // 0b0100101010
    MOV64_MEMORY_MEMORY_F_F,                                            // 0b0100101011
    MOV64_MEMORY_MEMORY_N_N,                                            // 0b0100101100
    MOV64_MEMORY_MEMORY_F_F,                                            // 0b0100101101
};



bool MOV_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (MOV_MODES[Mode]) ? MOV_MODES[Mode](PASS_ARGUMENTS) : false;
}