#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)


COMPARISON_FUNCS(NE, 8, int8_t, !=)
COMPARISON_FUNCS(NE, 16, int16_t, !=)
COMPARISON_FUNCS(NE, 32, int32_t, !=)
COMPARISON_FUNCS(NE, 64, int64_t, !=)



static bool (*CMPNE_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE8_NUM_REGISTER_N,                                              // 0b0000001010
    CMPNE8_NUM_REGISTER_F,                                              // 0b0000001011
    CMPNE8_NUM_MEMORY_N,                                                // 0b0000001100
    CMPNE8_NUM_MEMORY_F,                                                // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE8_REGISTER_REGISTER_N_N,                                       // 0b0000010010
    CMPNE8_REGISTER_REGISTER_N_F,                                       // 0b0000010011
    CMPNE8_REGISTER_MEMORY_N_N,                                         // 0b0000010100
    CMPNE8_REGISTER_MEMORY_N_F,                                         // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE8_REGISTER_REGISTER_F_N,                                       // 0b0000011010
    CMPNE8_REGISTER_REGISTER_F_F,                                       // 0b0000011011
    CMPNE8_REGISTER_MEMORY_F_N,                                         // 0b0000011100
    CMPNE8_REGISTER_MEMORY_F_F,                                         // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE8_MEMORY_REGISTER_N_N,                                         // 0b0000100010
    CMPNE8_MEMORY_REGISTER_N_F,                                         // 0b0000100011
    CMPNE8_MEMORY_MEMORY_N_N,                                           // 0b0000100100
    CMPNE8_MEMORY_MEMORY_N_F,                                           // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE8_MEMORY_REGISTER_F_N,                                         // 0b0000101010
    CMPNE8_MEMORY_MEMORY_F_F,                                           // 0b0000101011
    CMPNE8_MEMORY_MEMORY_N_N,                                           // 0b0000101100
    CMPNE8_MEMORY_MEMORY_F_F,                                           // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE16_NUM_REGISTER_N,                                             // 0b0001001010
    CMPNE16_NUM_REGISTER_F,                                             // 0b0001001011
    CMPNE16_NUM_MEMORY_N,                                               // 0b0001001100
    CMPNE16_NUM_MEMORY_F,                                               // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE16_REGISTER_REGISTER_N_N,                                      // 0b0001010010
    CMPNE16_REGISTER_REGISTER_N_F,                                      // 0b0001010011
    CMPNE16_REGISTER_MEMORY_N_N,                                        // 0b0001010100
    CMPNE16_REGISTER_MEMORY_N_F,                                        // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE16_REGISTER_REGISTER_F_N,                                      // 0b0001011010
    CMPNE16_REGISTER_REGISTER_F_F,                                      // 0b0001011011
    CMPNE16_REGISTER_MEMORY_F_N,                                        // 0b0001011100
    CMPNE16_REGISTER_MEMORY_F_F,                                        // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE16_MEMORY_REGISTER_N_N,                                        // 0b0001100010
    CMPNE16_MEMORY_REGISTER_N_F,                                        // 0b0001100011
    CMPNE16_MEMORY_MEMORY_N_N,                                          // 0b0001100100
    CMPNE16_MEMORY_MEMORY_N_F,                                          // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE16_MEMORY_REGISTER_F_N,                                        // 0b0001101010
    CMPNE16_MEMORY_MEMORY_F_F,                                          // 0b0001101011
    CMPNE16_MEMORY_MEMORY_N_N,                                          // 0b0001101100
    CMPNE16_MEMORY_MEMORY_F_F,                                          // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE32_NUM_REGISTER_N,                                             // 0b0010001010
    CMPNE32_NUM_REGISTER_F,                                             // 0b0010001011
    CMPNE32_NUM_MEMORY_N,                                               // 0b0010001100
    CMPNE32_NUM_MEMORY_F,                                               // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE32_REGISTER_REGISTER_N_N,                                      // 0b0010010010
    CMPNE32_REGISTER_REGISTER_N_F,                                      // 0b0010010011
    CMPNE32_REGISTER_MEMORY_N_N,                                        // 0b0010010100
    CMPNE32_REGISTER_MEMORY_N_F,                                        // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE32_REGISTER_REGISTER_F_N,                                      // 0b0010011010
    CMPNE32_REGISTER_REGISTER_F_F,                                      // 0b0010011011
    CMPNE32_REGISTER_MEMORY_F_N,                                        // 0b0010011100
    CMPNE32_REGISTER_MEMORY_F_F,                                        // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE32_MEMORY_REGISTER_N_N,                                        // 0b0010100010
    CMPNE32_MEMORY_REGISTER_N_F,                                        // 0b0010100011
    CMPNE32_MEMORY_MEMORY_N_N,                                          // 0b0010100100
    CMPNE32_MEMORY_MEMORY_N_F,                                          // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE32_MEMORY_REGISTER_F_N,                                        // 0b0010101010
    CMPNE32_MEMORY_MEMORY_F_F,                                          // 0b0010101011
    CMPNE32_MEMORY_MEMORY_N_N,                                          // 0b0010101100
    CMPNE32_MEMORY_MEMORY_F_F,                                          // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE64_NUM_REGISTER_N,                                             // 0b0100001010
    CMPNE64_NUM_REGISTER_F,                                             // 0b0100001011
    CMPNE64_NUM_MEMORY_N,                                               // 0b0100001100
    CMPNE64_NUM_MEMORY_F,                                               // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE64_REGISTER_REGISTER_N_N,                                      // 0b0100010010
    CMPNE64_REGISTER_REGISTER_N_F,                                      // 0b0100010011
    CMPNE64_REGISTER_MEMORY_N_N,                                        // 0b0100010100
    CMPNE64_REGISTER_MEMORY_N_F,                                        // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE64_REGISTER_REGISTER_F_N,                                      // 0b0100011010
    CMPNE64_REGISTER_REGISTER_F_F,                                      // 0b0100011011
    CMPNE64_REGISTER_MEMORY_F_N,                                        // 0b0100011100
    CMPNE64_REGISTER_MEMORY_F_F,                                        // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE64_MEMORY_REGISTER_N_N,                                        // 0b0100100010
    CMPNE64_MEMORY_REGISTER_N_F,                                        // 0b0100100011
    CMPNE64_MEMORY_MEMORY_N_N,                                          // 0b0100100100
    CMPNE64_MEMORY_MEMORY_N_F,                                          // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPNE64_MEMORY_REGISTER_F_N,                                        // 0b0100101010
    CMPNE64_MEMORY_MEMORY_F_F,                                          // 0b0100101011
    CMPNE64_MEMORY_MEMORY_N_N,                                          // 0b0100101100
    CMPNE64_MEMORY_MEMORY_F_F,                                          // 0b0100101101
};



bool CMPNE_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (CMPNE_MODES[Mode]) ? CMPNE_MODES[Mode](PASS_ARGUMENTS) : false;
}