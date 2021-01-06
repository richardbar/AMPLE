#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(AND, 8, int8_t, &=)
ASSIGNMENT_FUNCS(AND, 16, int16_t, &=)
ASSIGNMENT_FUNCS(AND, 32, int32_t, &=)
ASSIGNMENT_FUNCS(AND, 64, int64_t, &=)



static bool (*AND_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    AND8_NUM_REGISTER_N,                                                // 0b0000001010
    AND8_NUM_REGISTER_F,                                                // 0b0000001011
    AND8_NUM_MEMORY_N,                                                  // 0b0000001100
    AND8_NUM_MEMORY_F,                                                  // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    AND8_REGISTER_REGISTER_N_N,                                         // 0b0000010010
    AND8_REGISTER_REGISTER_N_F,                                         // 0b0000010011
    AND8_REGISTER_MEMORY_N_N,                                           // 0b0000010100
    AND8_REGISTER_MEMORY_N_F,                                           // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    AND8_REGISTER_REGISTER_F_N,                                         // 0b0000011010
    AND8_REGISTER_REGISTER_F_F,                                         // 0b0000011011
    AND8_REGISTER_MEMORY_F_N,                                           // 0b0000011100
    AND8_REGISTER_MEMORY_F_F,                                           // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    AND8_MEMORY_REGISTER_N_N,                                           // 0b0000100010
    AND8_MEMORY_REGISTER_N_F,                                           // 0b0000100011
    AND8_MEMORY_MEMORY_N_N,                                             // 0b0000100100
    AND8_MEMORY_MEMORY_N_F,                                             // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    AND8_MEMORY_REGISTER_F_N,                                           // 0b0000101010
    AND8_MEMORY_MEMORY_F_F,                                             // 0b0000101011
    AND8_MEMORY_MEMORY_N_N,                                             // 0b0000101100
    AND8_MEMORY_MEMORY_F_F,                                             // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    AND16_NUM_REGISTER_N,                                               // 0b0001001010
    AND16_NUM_REGISTER_F,                                               // 0b0001001011
    AND16_NUM_MEMORY_N,                                                 // 0b0001001100
    AND16_NUM_MEMORY_F,                                                 // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    AND16_REGISTER_REGISTER_N_N,                                        // 0b0001010010
    AND16_REGISTER_REGISTER_N_F,                                        // 0b0001010011
    AND16_REGISTER_MEMORY_N_N,                                          // 0b0001010100
    AND16_REGISTER_MEMORY_N_F,                                          // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    AND16_REGISTER_REGISTER_F_N,                                        // 0b0001011010
    AND16_REGISTER_REGISTER_F_F,                                        // 0b0001011011
    AND16_REGISTER_MEMORY_F_N,                                          // 0b0001011100
    AND16_REGISTER_MEMORY_F_F,                                          // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    AND16_MEMORY_REGISTER_N_N,                                          // 0b0001100010
    AND16_MEMORY_REGISTER_N_F,                                          // 0b0001100011
    AND16_MEMORY_MEMORY_N_N,                                            // 0b0001100100
    AND16_MEMORY_MEMORY_N_F,                                            // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    AND16_MEMORY_REGISTER_F_N,                                          // 0b0001101010
    AND16_MEMORY_MEMORY_F_F,                                            // 0b0001101011
    AND16_MEMORY_MEMORY_N_N,                                            // 0b0001101100
    AND16_MEMORY_MEMORY_F_F,                                            // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    AND32_NUM_REGISTER_N,                                               // 0b0010001010
    AND32_NUM_REGISTER_F,                                               // 0b0010001011
    AND32_NUM_MEMORY_N,                                                 // 0b0010001100
    AND32_NUM_MEMORY_F,                                                 // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    AND32_REGISTER_REGISTER_N_N,                                        // 0b0010010010
    AND32_REGISTER_REGISTER_N_F,                                        // 0b0010010011
    AND32_REGISTER_MEMORY_N_N,                                          // 0b0010010100
    AND32_REGISTER_MEMORY_N_F,                                          // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    AND32_REGISTER_REGISTER_F_N,                                        // 0b0010011010
    AND32_REGISTER_REGISTER_F_F,                                        // 0b0010011011
    AND32_REGISTER_MEMORY_F_N,                                          // 0b0010011100
    AND32_REGISTER_MEMORY_F_F,                                          // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    AND32_MEMORY_REGISTER_N_N,                                          // 0b0010100010
    AND32_MEMORY_REGISTER_N_F,                                          // 0b0010100011
    AND32_MEMORY_MEMORY_N_N,                                            // 0b0010100100
    AND32_MEMORY_MEMORY_N_F,                                            // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    AND32_MEMORY_REGISTER_F_N,                                          // 0b0010101010
    AND32_MEMORY_MEMORY_F_F,                                            // 0b0010101011
    AND32_MEMORY_MEMORY_N_N,                                            // 0b0010101100
    AND32_MEMORY_MEMORY_F_F,                                            // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    AND64_NUM_REGISTER_N,                                               // 0b0100001010
    AND64_NUM_REGISTER_F,                                               // 0b0100001011
    AND64_NUM_MEMORY_N,                                                 // 0b0100001100
    AND64_NUM_MEMORY_F,                                                 // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    AND64_REGISTER_REGISTER_N_N,                                        // 0b0100010010
    AND64_REGISTER_REGISTER_N_F,                                        // 0b0100010011
    AND64_REGISTER_MEMORY_N_N,                                          // 0b0100010100
    AND64_REGISTER_MEMORY_N_F,                                          // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    AND64_REGISTER_REGISTER_F_N,                                        // 0b0100011010
    AND64_REGISTER_REGISTER_F_F,                                        // 0b0100011011
    AND64_REGISTER_MEMORY_F_N,                                          // 0b0100011100
    AND64_REGISTER_MEMORY_F_F,                                          // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    AND64_MEMORY_REGISTER_N_N,                                          // 0b0100100010
    AND64_MEMORY_REGISTER_N_F,                                          // 0b0100100011
    AND64_MEMORY_MEMORY_N_N,                                            // 0b0100100100
    AND64_MEMORY_MEMORY_N_F,                                            // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    AND64_MEMORY_REGISTER_F_N,                                          // 0b0100101010
    AND64_MEMORY_MEMORY_F_F,                                            // 0b0100101011
    AND64_MEMORY_MEMORY_N_N,                                            // 0b0100101100
    AND64_MEMORY_MEMORY_F_F,                                            // 0b0100101101
};



bool AND_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (AND_MODES[Mode]) ? AND_MODES[Mode](PASS_ARGUMENTS) : false;
}