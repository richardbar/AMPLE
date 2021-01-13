#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)


COMPARISON_FUNCS(LE, 8, int8_t, <=)
COMPARISON_FUNCS(LE, 16, int16_t, <=)
COMPARISON_FUNCS(LE, 32, int32_t, <=)
COMPARISON_FUNCS(LE, 64, int64_t, <=)



static bool (*CMPLE_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE8_NUM_REGISTER_N,                                              // 0b0000001010
    CMPLE8_NUM_REGISTER_F,                                              // 0b0000001011
    CMPLE8_NUM_MEMORY_N,                                                // 0b0000001100
    CMPLE8_NUM_MEMORY_F,                                                // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE8_REGISTER_REGISTER_N_N,                                       // 0b0000010010
    CMPLE8_REGISTER_REGISTER_N_F,                                       // 0b0000010011
    CMPLE8_REGISTER_MEMORY_N_N,                                         // 0b0000010100
    CMPLE8_REGISTER_MEMORY_N_F,                                         // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE8_REGISTER_REGISTER_F_N,                                       // 0b0000011010
    CMPLE8_REGISTER_REGISTER_F_F,                                       // 0b0000011011
    CMPLE8_REGISTER_MEMORY_F_N,                                         // 0b0000011100
    CMPLE8_REGISTER_MEMORY_F_F,                                         // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE8_MEMORY_REGISTER_N_N,                                         // 0b0000100010
    CMPLE8_MEMORY_REGISTER_N_F,                                         // 0b0000100011
    CMPLE8_MEMORY_MEMORY_N_N,                                           // 0b0000100100
    CMPLE8_MEMORY_MEMORY_N_F,                                           // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE8_MEMORY_REGISTER_F_N,                                         // 0b0000101010
    CMPLE8_MEMORY_MEMORY_F_F,                                           // 0b0000101011
    CMPLE8_MEMORY_MEMORY_N_N,                                           // 0b0000101100
    CMPLE8_MEMORY_MEMORY_F_F,                                           // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE16_NUM_REGISTER_N,                                             // 0b0001001010
    CMPLE16_NUM_REGISTER_F,                                             // 0b0001001011
    CMPLE16_NUM_MEMORY_N,                                               // 0b0001001100
    CMPLE16_NUM_MEMORY_F,                                               // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE16_REGISTER_REGISTER_N_N,                                      // 0b0001010010
    CMPLE16_REGISTER_REGISTER_N_F,                                      // 0b0001010011
    CMPLE16_REGISTER_MEMORY_N_N,                                        // 0b0001010100
    CMPLE16_REGISTER_MEMORY_N_F,                                        // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE16_REGISTER_REGISTER_F_N,                                      // 0b0001011010
    CMPLE16_REGISTER_REGISTER_F_F,                                      // 0b0001011011
    CMPLE16_REGISTER_MEMORY_F_N,                                        // 0b0001011100
    CMPLE16_REGISTER_MEMORY_F_F,                                        // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE16_MEMORY_REGISTER_N_N,                                        // 0b0001100010
    CMPLE16_MEMORY_REGISTER_N_F,                                        // 0b0001100011
    CMPLE16_MEMORY_MEMORY_N_N,                                          // 0b0001100100
    CMPLE16_MEMORY_MEMORY_N_F,                                          // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE16_MEMORY_REGISTER_F_N,                                        // 0b0001101010
    CMPLE16_MEMORY_MEMORY_F_F,                                          // 0b0001101011
    CMPLE16_MEMORY_MEMORY_N_N,                                          // 0b0001101100
    CMPLE16_MEMORY_MEMORY_F_F,                                          // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE32_NUM_REGISTER_N,                                             // 0b0010001010
    CMPLE32_NUM_REGISTER_F,                                             // 0b0010001011
    CMPLE32_NUM_MEMORY_N,                                               // 0b0010001100
    CMPLE32_NUM_MEMORY_F,                                               // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE32_REGISTER_REGISTER_N_N,                                      // 0b0010010010
    CMPLE32_REGISTER_REGISTER_N_F,                                      // 0b0010010011
    CMPLE32_REGISTER_MEMORY_N_N,                                        // 0b0010010100
    CMPLE32_REGISTER_MEMORY_N_F,                                        // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE32_REGISTER_REGISTER_F_N,                                      // 0b0010011010
    CMPLE32_REGISTER_REGISTER_F_F,                                      // 0b0010011011
    CMPLE32_REGISTER_MEMORY_F_N,                                        // 0b0010011100
    CMPLE32_REGISTER_MEMORY_F_F,                                        // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE32_MEMORY_REGISTER_N_N,                                        // 0b0010100010
    CMPLE32_MEMORY_REGISTER_N_F,                                        // 0b0010100011
    CMPLE32_MEMORY_MEMORY_N_N,                                          // 0b0010100100
    CMPLE32_MEMORY_MEMORY_N_F,                                          // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE32_MEMORY_REGISTER_F_N,                                        // 0b0010101010
    CMPLE32_MEMORY_MEMORY_F_F,                                          // 0b0010101011
    CMPLE32_MEMORY_MEMORY_N_N,                                          // 0b0010101100
    CMPLE32_MEMORY_MEMORY_F_F,                                          // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE64_NUM_REGISTER_N,                                             // 0b0100001010
    CMPLE64_NUM_REGISTER_F,                                             // 0b0100001011
    CMPLE64_NUM_MEMORY_N,                                               // 0b0100001100
    CMPLE64_NUM_MEMORY_F,                                               // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE64_REGISTER_REGISTER_N_N,                                      // 0b0100010010
    CMPLE64_REGISTER_REGISTER_N_F,                                      // 0b0100010011
    CMPLE64_REGISTER_MEMORY_N_N,                                        // 0b0100010100
    CMPLE64_REGISTER_MEMORY_N_F,                                        // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE64_REGISTER_REGISTER_F_N,                                      // 0b0100011010
    CMPLE64_REGISTER_REGISTER_F_F,                                      // 0b0100011011
    CMPLE64_REGISTER_MEMORY_F_N,                                        // 0b0100011100
    CMPLE64_REGISTER_MEMORY_F_F,                                        // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE64_MEMORY_REGISTER_N_N,                                        // 0b0100100010
    CMPLE64_MEMORY_REGISTER_N_F,                                        // 0b0100100011
    CMPLE64_MEMORY_MEMORY_N_N,                                          // 0b0100100100
    CMPLE64_MEMORY_MEMORY_N_F,                                          // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLE64_MEMORY_REGISTER_F_N,                                        // 0b0100101010
    CMPLE64_MEMORY_MEMORY_F_F,                                          // 0b0100101011
    CMPLE64_MEMORY_MEMORY_N_N,                                          // 0b0100101100
    CMPLE64_MEMORY_MEMORY_F_F,                                          // 0b0100101101
};



bool CMPLE_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (CMPLE_MODES[Mode]) ? CMPLE_MODES[Mode](PASS_ARGUMENTS) : false;
}