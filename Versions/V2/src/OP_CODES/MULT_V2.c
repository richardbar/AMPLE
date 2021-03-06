#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(MULT, 8, int8_t, *=)
ASSIGNMENT_FUNCS(MULT, 16, int16_t, *=)
ASSIGNMENT_FUNCS(MULT, 32, int32_t, *=)
ASSIGNMENT_FUNCS(MULT, 64, int64_t, *=)



static bool (*MULT_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MULT8_NUM_REGISTER_N,                                               // 0b0000001010
    MULT8_NUM_REGISTER_F,                                               // 0b0000001011
    MULT8_NUM_MEMORY_N,                                                 // 0b0000001100
    MULT8_NUM_MEMORY_F,                                                 // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT8_REGISTER_REGISTER_N_N,                                        // 0b0000010010
    MULT8_REGISTER_REGISTER_N_F,                                        // 0b0000010011
    MULT8_REGISTER_MEMORY_N_N,                                          // 0b0000010100
    MULT8_REGISTER_MEMORY_N_F,                                          // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT8_REGISTER_REGISTER_F_N,                                        // 0b0000011010
    MULT8_REGISTER_REGISTER_F_F,                                        // 0b0000011011
    MULT8_REGISTER_MEMORY_F_N,                                          // 0b0000011100
    MULT8_REGISTER_MEMORY_F_F,                                          // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT8_MEMORY_REGISTER_N_N,                                          // 0b0000100010
    MULT8_MEMORY_REGISTER_N_F,                                          // 0b0000100011
    MULT8_MEMORY_MEMORY_N_N,                                            // 0b0000100100
    MULT8_MEMORY_MEMORY_N_F,                                            // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT8_MEMORY_REGISTER_F_N,                                          // 0b0000101010
    MULT8_MEMORY_MEMORY_F_F,                                            // 0b0000101011
    MULT8_MEMORY_MEMORY_N_N,                                            // 0b0000101100
    MULT8_MEMORY_MEMORY_F_F,                                            // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MULT16_NUM_REGISTER_N,                                              // 0b0001001010
    MULT16_NUM_REGISTER_F,                                              // 0b0001001011
    MULT16_NUM_MEMORY_N,                                                // 0b0001001100
    MULT16_NUM_MEMORY_F,                                                // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT16_REGISTER_REGISTER_N_N,                                       // 0b0001010010
    MULT16_REGISTER_REGISTER_N_F,                                       // 0b0001010011
    MULT16_REGISTER_MEMORY_N_N,                                         // 0b0001010100
    MULT16_REGISTER_MEMORY_N_F,                                         // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT16_REGISTER_REGISTER_F_N,                                       // 0b0001011010
    MULT16_REGISTER_REGISTER_F_F,                                       // 0b0001011011
    MULT16_REGISTER_MEMORY_F_N,                                         // 0b0001011100
    MULT16_REGISTER_MEMORY_F_F,                                         // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT16_MEMORY_REGISTER_N_N,                                         // 0b0001100010
    MULT16_MEMORY_REGISTER_N_F,                                         // 0b0001100011
    MULT16_MEMORY_MEMORY_N_N,                                           // 0b0001100100
    MULT16_MEMORY_MEMORY_N_F,                                           // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT16_MEMORY_REGISTER_F_N,                                         // 0b0001101010
    MULT16_MEMORY_MEMORY_F_F,                                           // 0b0001101011
    MULT16_MEMORY_MEMORY_N_N,                                           // 0b0001101100
    MULT16_MEMORY_MEMORY_F_F,                                           // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MULT32_NUM_REGISTER_N,                                              // 0b0010001010
    MULT32_NUM_REGISTER_F,                                              // 0b0010001011
    MULT32_NUM_MEMORY_N,                                                // 0b0010001100
    MULT32_NUM_MEMORY_F,                                                // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT32_REGISTER_REGISTER_N_N,                                       // 0b0010010010
    MULT32_REGISTER_REGISTER_N_F,                                       // 0b0010010011
    MULT32_REGISTER_MEMORY_N_N,                                         // 0b0010010100
    MULT32_REGISTER_MEMORY_N_F,                                         // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT32_REGISTER_REGISTER_F_N,                                       // 0b0010011010
    MULT32_REGISTER_REGISTER_F_F,                                       // 0b0010011011
    MULT32_REGISTER_MEMORY_F_N,                                         // 0b0010011100
    MULT32_REGISTER_MEMORY_F_F,                                         // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT32_MEMORY_REGISTER_N_N,                                         // 0b0010100010
    MULT32_MEMORY_REGISTER_N_F,                                         // 0b0010100011
    MULT32_MEMORY_MEMORY_N_N,                                           // 0b0010100100
    MULT32_MEMORY_MEMORY_N_F,                                           // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT32_MEMORY_REGISTER_F_N,                                         // 0b0010101010
    MULT32_MEMORY_MEMORY_F_F,                                           // 0b0010101011
    MULT32_MEMORY_MEMORY_N_N,                                           // 0b0010101100
    MULT32_MEMORY_MEMORY_F_F,                                           // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    MULT64_NUM_REGISTER_N,                                              // 0b0100001010
    MULT64_NUM_REGISTER_F,                                              // 0b0100001011
    MULT64_NUM_MEMORY_N,                                                // 0b0100001100
    MULT64_NUM_MEMORY_F,                                                // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT64_REGISTER_REGISTER_N_N,                                       // 0b0100010010
    MULT64_REGISTER_REGISTER_N_F,                                       // 0b0100010011
    MULT64_REGISTER_MEMORY_N_N,                                         // 0b0100010100
    MULT64_REGISTER_MEMORY_N_F,                                         // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT64_REGISTER_REGISTER_F_N,                                       // 0b0100011010
    MULT64_REGISTER_REGISTER_F_F,                                       // 0b0100011011
    MULT64_REGISTER_MEMORY_F_N,                                         // 0b0100011100
    MULT64_REGISTER_MEMORY_F_F,                                         // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT64_MEMORY_REGISTER_N_N,                                         // 0b0100100010
    MULT64_MEMORY_REGISTER_N_F,                                         // 0b0100100011
    MULT64_MEMORY_MEMORY_N_N,                                           // 0b0100100100
    MULT64_MEMORY_MEMORY_N_F,                                           // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    MULT64_MEMORY_REGISTER_F_N,                                         // 0b0100101010
    MULT64_MEMORY_MEMORY_F_F,                                           // 0b0100101011
    MULT64_MEMORY_MEMORY_N_N,                                           // 0b0100101100
    MULT64_MEMORY_MEMORY_F_F,                                           // 0b0100101101
};



bool MULT_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (MULT_MODES[Mode]) ? MULT_MODES[Mode](PASS_ARGUMENTS) : false;
}