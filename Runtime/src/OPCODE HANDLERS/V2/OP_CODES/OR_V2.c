#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(OR, 8, int8_t, |=)
ASSIGNMENT_FUNCS(OR, 16, int16_t, |=)
ASSIGNMENT_FUNCS(OR, 32, int32_t, |=)
ASSIGNMENT_FUNCS(OR, 64, int64_t, |=)



static bool (*OR_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    OR8_NUM_REGISTER_N,                                                 // 0b0000001010
    OR8_NUM_REGISTER_F,                                                 // 0b0000001011
    OR8_NUM_MEMORY_N,                                                   // 0b0000001100
    OR8_NUM_MEMORY_F,                                                   // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    OR8_REGISTER_REGISTER_N_N,                                          // 0b0000010010
    OR8_REGISTER_REGISTER_N_F,                                          // 0b0000010011
    OR8_REGISTER_MEMORY_N_N,                                            // 0b0000010100
    OR8_REGISTER_MEMORY_N_F,                                            // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    OR8_REGISTER_REGISTER_F_N,                                          // 0b0000011010
    OR8_REGISTER_REGISTER_F_F,                                          // 0b0000011011
    OR8_REGISTER_MEMORY_F_N,                                            // 0b0000011100
    OR8_REGISTER_MEMORY_F_F,                                            // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    OR8_MEMORY_REGISTER_N_N,                                            // 0b0000100010
    OR8_MEMORY_REGISTER_N_F,                                            // 0b0000100011
    OR8_MEMORY_MEMORY_N_N,                                              // 0b0000100100
    OR8_MEMORY_MEMORY_N_F,                                              // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    OR8_MEMORY_REGISTER_F_N,                                            // 0b0000101010
    OR8_MEMORY_MEMORY_F_F,                                              // 0b0000101011
    OR8_MEMORY_MEMORY_N_N,                                              // 0b0000101100
    OR8_MEMORY_MEMORY_F_F,                                              // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    OR16_NUM_REGISTER_N,                                                // 0b0001001010
    OR16_NUM_REGISTER_F,                                                // 0b0001001011
    OR16_NUM_MEMORY_N,                                                  // 0b0001001100
    OR16_NUM_MEMORY_F,                                                  // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    OR16_REGISTER_REGISTER_N_N,                                         // 0b0001010010
    OR16_REGISTER_REGISTER_N_F,                                         // 0b0001010011
    OR16_REGISTER_MEMORY_N_N,                                           // 0b0001010100
    OR16_REGISTER_MEMORY_N_F,                                           // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    OR16_REGISTER_REGISTER_F_N,                                         // 0b0001011010
    OR16_REGISTER_REGISTER_F_F,                                         // 0b0001011011
    OR16_REGISTER_MEMORY_F_N,                                           // 0b0001011100
    OR16_REGISTER_MEMORY_F_F,                                           // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    OR16_MEMORY_REGISTER_N_N,                                           // 0b0001100010
    OR16_MEMORY_REGISTER_N_F,                                           // 0b0001100011
    OR16_MEMORY_MEMORY_N_N,                                             // 0b0001100100
    OR16_MEMORY_MEMORY_N_F,                                             // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    OR16_MEMORY_REGISTER_F_N,                                           // 0b0001101010
    OR16_MEMORY_MEMORY_F_F,                                             // 0b0001101011
    OR16_MEMORY_MEMORY_N_N,                                             // 0b0001101100
    OR16_MEMORY_MEMORY_F_F,                                             // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    OR32_NUM_REGISTER_N,                                                // 0b0010001010
    OR32_NUM_REGISTER_F,                                                // 0b0010001011
    OR32_NUM_MEMORY_N,                                                  // 0b0010001100
    OR32_NUM_MEMORY_F,                                                  // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    OR32_REGISTER_REGISTER_N_N,                                         // 0b0010010010
    OR32_REGISTER_REGISTER_N_F,                                         // 0b0010010011
    OR32_REGISTER_MEMORY_N_N,                                           // 0b0010010100
    OR32_REGISTER_MEMORY_N_F,                                           // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    OR32_REGISTER_REGISTER_F_N,                                         // 0b0010011010
    OR32_REGISTER_REGISTER_F_F,                                         // 0b0010011011
    OR32_REGISTER_MEMORY_F_N,                                           // 0b0010011100
    OR32_REGISTER_MEMORY_F_F,                                           // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    OR32_MEMORY_REGISTER_N_N,                                           // 0b0010100010
    OR32_MEMORY_REGISTER_N_F,                                           // 0b0010100011
    OR32_MEMORY_MEMORY_N_N,                                             // 0b0010100100
    OR32_MEMORY_MEMORY_N_F,                                             // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    OR32_MEMORY_REGISTER_F_N,                                           // 0b0010101010
    OR32_MEMORY_MEMORY_F_F,                                             // 0b0010101011
    OR32_MEMORY_MEMORY_N_N,                                             // 0b0010101100
    OR32_MEMORY_MEMORY_F_F,                                             // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    OR64_NUM_REGISTER_N,                                                // 0b0100001010
    OR64_NUM_REGISTER_F,                                                // 0b0100001011
    OR64_NUM_MEMORY_N,                                                  // 0b0100001100
    OR64_NUM_MEMORY_F,                                                  // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    OR64_REGISTER_REGISTER_N_N,                                         // 0b0100010010
    OR64_REGISTER_REGISTER_N_F,                                         // 0b0100010011
    OR64_REGISTER_MEMORY_N_N,                                           // 0b0100010100
    OR64_REGISTER_MEMORY_N_F,                                           // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    OR64_REGISTER_REGISTER_F_N,                                         // 0b0100011010
    OR64_REGISTER_REGISTER_F_F,                                         // 0b0100011011
    OR64_REGISTER_MEMORY_F_N,                                           // 0b0100011100
    OR64_REGISTER_MEMORY_F_F,                                           // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    OR64_MEMORY_REGISTER_N_N,                                           // 0b0100100010
    OR64_MEMORY_REGISTER_N_F,                                           // 0b0100100011
    OR64_MEMORY_MEMORY_N_N,                                             // 0b0100100100
    OR64_MEMORY_MEMORY_N_F,                                             // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    OR64_MEMORY_REGISTER_F_N,                                           // 0b0100101010
    OR64_MEMORY_MEMORY_F_F,                                             // 0b0100101011
    OR64_MEMORY_MEMORY_N_N,                                             // 0b0100101100
    OR64_MEMORY_MEMORY_F_F,                                             // 0b0100101101
};



bool OR_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (OR_MODES[Mode]) ? OR_MODES[Mode](PASS_ARGUMENTS) : false;
}