#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(SUB, 8, int8_t, -=)
ASSIGNMENT_FUNCS(SUB, 16, int16_t, -=)
ASSIGNMENT_FUNCS(SUB, 32, int32_t, -=)
ASSIGNMENT_FUNCS(SUB, 64, int64_t, -=)



static bool (*SUB_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    SUB8_NUM_REGISTER_N,                                                // 0b0000001010
    SUB8_NUM_REGISTER_F,                                                // 0b0000001011
    SUB8_NUM_MEMORY_N,                                                  // 0b0000001100
    SUB8_NUM_MEMORY_F,                                                  // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB8_REGISTER_REGISTER_N_N,                                         // 0b0000010010
    SUB8_REGISTER_REGISTER_N_F,                                         // 0b0000010011
    SUB8_REGISTER_MEMORY_N_N,                                           // 0b0000010100
    SUB8_REGISTER_MEMORY_N_F,                                           // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB8_REGISTER_REGISTER_F_N,                                         // 0b0000011010
    SUB8_REGISTER_REGISTER_F_F,                                         // 0b0000011011
    SUB8_REGISTER_MEMORY_F_N,                                           // 0b0000011100
    SUB8_REGISTER_MEMORY_F_F,                                           // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB8_MEMORY_REGISTER_N_N,                                           // 0b0000100010
    SUB8_MEMORY_REGISTER_N_F,                                           // 0b0000100011
    SUB8_MEMORY_MEMORY_N_N,                                             // 0b0000100100
    SUB8_MEMORY_MEMORY_N_F,                                             // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB8_MEMORY_REGISTER_F_N,                                           // 0b0000101010
    SUB8_MEMORY_MEMORY_F_F,                                             // 0b0000101011
    SUB8_MEMORY_MEMORY_N_N,                                             // 0b0000101100
    SUB8_MEMORY_MEMORY_F_F,                                             // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    SUB16_NUM_REGISTER_N,                                               // 0b0001001010
    SUB16_NUM_REGISTER_F,                                               // 0b0001001011
    SUB16_NUM_MEMORY_N,                                                 // 0b0001001100
    SUB16_NUM_MEMORY_F,                                                 // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB16_REGISTER_REGISTER_N_N,                                        // 0b0001010010
    SUB16_REGISTER_REGISTER_N_F,                                        // 0b0001010011
    SUB16_REGISTER_MEMORY_N_N,                                          // 0b0001010100
    SUB16_REGISTER_MEMORY_N_F,                                          // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB16_REGISTER_REGISTER_F_N,                                        // 0b0001011010
    SUB16_REGISTER_REGISTER_F_F,                                        // 0b0001011011
    SUB16_REGISTER_MEMORY_F_N,                                          // 0b0001011100
    SUB16_REGISTER_MEMORY_F_F,                                          // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB16_MEMORY_REGISTER_N_N,                                          // 0b0001100010
    SUB16_MEMORY_REGISTER_N_F,                                          // 0b0001100011
    SUB16_MEMORY_MEMORY_N_N,                                            // 0b0001100100
    SUB16_MEMORY_MEMORY_N_F,                                            // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB16_MEMORY_REGISTER_F_N,                                          // 0b0001101010
    SUB16_MEMORY_MEMORY_F_F,                                            // 0b0001101011
    SUB16_MEMORY_MEMORY_N_N,                                            // 0b0001101100
    SUB16_MEMORY_MEMORY_F_F,                                            // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    SUB32_NUM_REGISTER_N,                                               // 0b0010001010
    SUB32_NUM_REGISTER_F,                                               // 0b0010001011
    SUB32_NUM_MEMORY_N,                                                 // 0b0010001100
    SUB32_NUM_MEMORY_F,                                                 // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB32_REGISTER_REGISTER_N_N,                                        // 0b0010010010
    SUB32_REGISTER_REGISTER_N_F,                                        // 0b0010010011
    SUB32_REGISTER_MEMORY_N_N,                                          // 0b0010010100
    SUB32_REGISTER_MEMORY_N_F,                                          // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB32_REGISTER_REGISTER_F_N,                                        // 0b0010011010
    SUB32_REGISTER_REGISTER_F_F,                                        // 0b0010011011
    SUB32_REGISTER_MEMORY_F_N,                                          // 0b0010011100
    SUB32_REGISTER_MEMORY_F_F,                                          // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB32_MEMORY_REGISTER_N_N,                                          // 0b0010100010
    SUB32_MEMORY_REGISTER_N_F,                                          // 0b0010100011
    SUB32_MEMORY_MEMORY_N_N,                                            // 0b0010100100
    SUB32_MEMORY_MEMORY_N_F,                                            // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB32_MEMORY_REGISTER_F_N,                                          // 0b0010101010
    SUB32_MEMORY_MEMORY_F_F,                                            // 0b0010101011
    SUB32_MEMORY_MEMORY_N_N,                                            // 0b0010101100
    SUB32_MEMORY_MEMORY_F_F,                                            // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    SUB64_NUM_REGISTER_N,                                               // 0b0100001010
    SUB64_NUM_REGISTER_F,                                               // 0b0100001011
    SUB64_NUM_MEMORY_N,                                                 // 0b0100001100
    SUB64_NUM_MEMORY_F,                                                 // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB64_REGISTER_REGISTER_N_N,                                        // 0b0100010010
    SUB64_REGISTER_REGISTER_N_F,                                        // 0b0100010011
    SUB64_REGISTER_MEMORY_N_N,                                          // 0b0100010100
    SUB64_REGISTER_MEMORY_N_F,                                          // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB64_REGISTER_REGISTER_F_N,                                        // 0b0100011010
    SUB64_REGISTER_REGISTER_F_F,                                        // 0b0100011011
    SUB64_REGISTER_MEMORY_F_N,                                          // 0b0100011100
    SUB64_REGISTER_MEMORY_F_F,                                          // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB64_MEMORY_REGISTER_N_N,                                          // 0b0100100010
    SUB64_MEMORY_REGISTER_N_F,                                          // 0b0100100011
    SUB64_MEMORY_MEMORY_N_N,                                            // 0b0100100100
    SUB64_MEMORY_MEMORY_N_F,                                            // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    SUB64_MEMORY_REGISTER_F_N,                                          // 0b0100101010
    SUB64_MEMORY_MEMORY_F_F,                                            // 0b0100101011
    SUB64_MEMORY_MEMORY_N_N,                                            // 0b0100101100
    SUB64_MEMORY_MEMORY_F_F,                                            // 0b0100101101
};



bool SUB_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (SUB_MODES[Mode]) ? SUB_MODES[Mode](PASS_ARGUMENTS) : false;
}