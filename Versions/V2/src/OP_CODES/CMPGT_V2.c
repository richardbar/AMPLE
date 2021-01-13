#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)


COMPARISON_FUNCS(GT, 8, int8_t, >)
COMPARISON_FUNCS(GT, 16, int16_t, >)
COMPARISON_FUNCS(GT, 32, int32_t, >)
COMPARISON_FUNCS(GT, 64, int64_t, >)



static bool (*CMPGT_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT8_NUM_REGISTER_N,                                              // 0b0000001010
    CMPGT8_NUM_REGISTER_F,                                              // 0b0000001011
    CMPGT8_NUM_MEMORY_N,                                                // 0b0000001100
    CMPGT8_NUM_MEMORY_F,                                                // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT8_REGISTER_REGISTER_N_N,                                       // 0b0000010010
    CMPGT8_REGISTER_REGISTER_N_F,                                       // 0b0000010011
    CMPGT8_REGISTER_MEMORY_N_N,                                         // 0b0000010100
    CMPGT8_REGISTER_MEMORY_N_F,                                         // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT8_REGISTER_REGISTER_F_N,                                       // 0b0000011010
    CMPGT8_REGISTER_REGISTER_F_F,                                       // 0b0000011011
    CMPGT8_REGISTER_MEMORY_F_N,                                         // 0b0000011100
    CMPGT8_REGISTER_MEMORY_F_F,                                         // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT8_MEMORY_REGISTER_N_N,                                         // 0b0000100010
    CMPGT8_MEMORY_REGISTER_N_F,                                         // 0b0000100011
    CMPGT8_MEMORY_MEMORY_N_N,                                           // 0b0000100100
    CMPGT8_MEMORY_MEMORY_N_F,                                           // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT8_MEMORY_REGISTER_F_N,                                         // 0b0000101010
    CMPGT8_MEMORY_MEMORY_F_F,                                           // 0b0000101011
    CMPGT8_MEMORY_MEMORY_N_N,                                           // 0b0000101100
    CMPGT8_MEMORY_MEMORY_F_F,                                           // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT16_NUM_REGISTER_N,                                             // 0b0001001010
    CMPGT16_NUM_REGISTER_F,                                             // 0b0001001011
    CMPGT16_NUM_MEMORY_N,                                               // 0b0001001100
    CMPGT16_NUM_MEMORY_F,                                               // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT16_REGISTER_REGISTER_N_N,                                      // 0b0001010010
    CMPGT16_REGISTER_REGISTER_N_F,                                      // 0b0001010011
    CMPGT16_REGISTER_MEMORY_N_N,                                        // 0b0001010100
    CMPGT16_REGISTER_MEMORY_N_F,                                        // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT16_REGISTER_REGISTER_F_N,                                      // 0b0001011010
    CMPGT16_REGISTER_REGISTER_F_F,                                      // 0b0001011011
    CMPGT16_REGISTER_MEMORY_F_N,                                        // 0b0001011100
    CMPGT16_REGISTER_MEMORY_F_F,                                        // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT16_MEMORY_REGISTER_N_N,                                        // 0b0001100010
    CMPGT16_MEMORY_REGISTER_N_F,                                        // 0b0001100011
    CMPGT16_MEMORY_MEMORY_N_N,                                          // 0b0001100100
    CMPGT16_MEMORY_MEMORY_N_F,                                          // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT16_MEMORY_REGISTER_F_N,                                        // 0b0001101010
    CMPGT16_MEMORY_MEMORY_F_F,                                          // 0b0001101011
    CMPGT16_MEMORY_MEMORY_N_N,                                          // 0b0001101100
    CMPGT16_MEMORY_MEMORY_F_F,                                          // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT32_NUM_REGISTER_N,                                             // 0b0010001010
    CMPGT32_NUM_REGISTER_F,                                             // 0b0010001011
    CMPGT32_NUM_MEMORY_N,                                               // 0b0010001100
    CMPGT32_NUM_MEMORY_F,                                               // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT32_REGISTER_REGISTER_N_N,                                      // 0b0010010010
    CMPGT32_REGISTER_REGISTER_N_F,                                      // 0b0010010011
    CMPGT32_REGISTER_MEMORY_N_N,                                        // 0b0010010100
    CMPGT32_REGISTER_MEMORY_N_F,                                        // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT32_REGISTER_REGISTER_F_N,                                      // 0b0010011010
    CMPGT32_REGISTER_REGISTER_F_F,                                      // 0b0010011011
    CMPGT32_REGISTER_MEMORY_F_N,                                        // 0b0010011100
    CMPGT32_REGISTER_MEMORY_F_F,                                        // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT32_MEMORY_REGISTER_N_N,                                        // 0b0010100010
    CMPGT32_MEMORY_REGISTER_N_F,                                        // 0b0010100011
    CMPGT32_MEMORY_MEMORY_N_N,                                          // 0b0010100100
    CMPGT32_MEMORY_MEMORY_N_F,                                          // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT32_MEMORY_REGISTER_F_N,                                        // 0b0010101010
    CMPGT32_MEMORY_MEMORY_F_F,                                          // 0b0010101011
    CMPGT32_MEMORY_MEMORY_N_N,                                          // 0b0010101100
    CMPGT32_MEMORY_MEMORY_F_F,                                          // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT64_NUM_REGISTER_N,                                             // 0b0100001010
    CMPGT64_NUM_REGISTER_F,                                             // 0b0100001011
    CMPGT64_NUM_MEMORY_N,                                               // 0b0100001100
    CMPGT64_NUM_MEMORY_F,                                               // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT64_REGISTER_REGISTER_N_N,                                      // 0b0100010010
    CMPGT64_REGISTER_REGISTER_N_F,                                      // 0b0100010011
    CMPGT64_REGISTER_MEMORY_N_N,                                        // 0b0100010100
    CMPGT64_REGISTER_MEMORY_N_F,                                        // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT64_REGISTER_REGISTER_F_N,                                      // 0b0100011010
    CMPGT64_REGISTER_REGISTER_F_F,                                      // 0b0100011011
    CMPGT64_REGISTER_MEMORY_F_N,                                        // 0b0100011100
    CMPGT64_REGISTER_MEMORY_F_F,                                        // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT64_MEMORY_REGISTER_N_N,                                        // 0b0100100010
    CMPGT64_MEMORY_REGISTER_N_F,                                        // 0b0100100011
    CMPGT64_MEMORY_MEMORY_N_N,                                          // 0b0100100100
    CMPGT64_MEMORY_MEMORY_N_F,                                          // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGT64_MEMORY_REGISTER_F_N,                                        // 0b0100101010
    CMPGT64_MEMORY_MEMORY_F_F,                                          // 0b0100101011
    CMPGT64_MEMORY_MEMORY_N_N,                                          // 0b0100101100
    CMPGT64_MEMORY_MEMORY_F_F,                                          // 0b0100101101
};



bool CMPGT_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (CMPGT_MODES[Mode]) ? CMPGT_MODES[Mode](PASS_ARGUMENTS) : false;
}