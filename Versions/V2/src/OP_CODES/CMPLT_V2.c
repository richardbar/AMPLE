#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)


COMPARISON_FUNCS(LT, 8, int8_t, <)
COMPARISON_FUNCS(LT, 16, int16_t, <)
COMPARISON_FUNCS(LT, 32, int32_t, <)
COMPARISON_FUNCS(LT, 64, int64_t, <)



static bool (*CMPLT_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT8_NUM_REGISTER_N,                                              // 0b0000001010
    CMPLT8_NUM_REGISTER_F,                                              // 0b0000001011
    CMPLT8_NUM_MEMORY_N,                                                // 0b0000001100
    CMPLT8_NUM_MEMORY_F,                                                // 0b0000001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT8_REGISTER_REGISTER_N_N,                                       // 0b0000010010
    CMPLT8_REGISTER_REGISTER_N_F,                                       // 0b0000010011
    CMPLT8_REGISTER_MEMORY_N_N,                                         // 0b0000010100
    CMPLT8_REGISTER_MEMORY_N_F,                                         // 0b0000010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT8_REGISTER_REGISTER_F_N,                                       // 0b0000011010
    CMPLT8_REGISTER_REGISTER_F_F,                                       // 0b0000011011
    CMPLT8_REGISTER_MEMORY_F_N,                                         // 0b0000011100
    CMPLT8_REGISTER_MEMORY_F_F,                                         // 0b0000011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT8_MEMORY_REGISTER_N_N,                                         // 0b0000100010
    CMPLT8_MEMORY_REGISTER_N_F,                                         // 0b0000100011
    CMPLT8_MEMORY_MEMORY_N_N,                                           // 0b0000100100
    CMPLT8_MEMORY_MEMORY_N_F,                                           // 0b0000100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT8_MEMORY_REGISTER_F_N,                                         // 0b0000101010
    CMPLT8_MEMORY_MEMORY_F_F,                                           // 0b0000101011
    CMPLT8_MEMORY_MEMORY_N_N,                                           // 0b0000101100
    CMPLT8_MEMORY_MEMORY_F_F,                                           // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT16_NUM_REGISTER_N,                                             // 0b0001001010
    CMPLT16_NUM_REGISTER_F,                                             // 0b0001001011
    CMPLT16_NUM_MEMORY_N,                                               // 0b0001001100
    CMPLT16_NUM_MEMORY_F,                                               // 0b0001001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT16_REGISTER_REGISTER_N_N,                                      // 0b0001010010
    CMPLT16_REGISTER_REGISTER_N_F,                                      // 0b0001010011
    CMPLT16_REGISTER_MEMORY_N_N,                                        // 0b0001010100
    CMPLT16_REGISTER_MEMORY_N_F,                                        // 0b0001010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT16_REGISTER_REGISTER_F_N,                                      // 0b0001011010
    CMPLT16_REGISTER_REGISTER_F_F,                                      // 0b0001011011
    CMPLT16_REGISTER_MEMORY_F_N,                                        // 0b0001011100
    CMPLT16_REGISTER_MEMORY_F_F,                                        // 0b0001011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT16_MEMORY_REGISTER_N_N,                                        // 0b0001100010
    CMPLT16_MEMORY_REGISTER_N_F,                                        // 0b0001100011
    CMPLT16_MEMORY_MEMORY_N_N,                                          // 0b0001100100
    CMPLT16_MEMORY_MEMORY_N_F,                                          // 0b0001100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT16_MEMORY_REGISTER_F_N,                                        // 0b0001101010
    CMPLT16_MEMORY_MEMORY_F_F,                                          // 0b0001101011
    CMPLT16_MEMORY_MEMORY_N_N,                                          // 0b0001101100
    CMPLT16_MEMORY_MEMORY_F_F,                                          // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT32_NUM_REGISTER_N,                                             // 0b0010001010
    CMPLT32_NUM_REGISTER_F,                                             // 0b0010001011
    CMPLT32_NUM_MEMORY_N,                                               // 0b0010001100
    CMPLT32_NUM_MEMORY_F,                                               // 0b0010001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT32_REGISTER_REGISTER_N_N,                                      // 0b0010010010
    CMPLT32_REGISTER_REGISTER_N_F,                                      // 0b0010010011
    CMPLT32_REGISTER_MEMORY_N_N,                                        // 0b0010010100
    CMPLT32_REGISTER_MEMORY_N_F,                                        // 0b0010010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT32_REGISTER_REGISTER_F_N,                                      // 0b0010011010
    CMPLT32_REGISTER_REGISTER_F_F,                                      // 0b0010011011
    CMPLT32_REGISTER_MEMORY_F_N,                                        // 0b0010011100
    CMPLT32_REGISTER_MEMORY_F_F,                                        // 0b0010011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT32_MEMORY_REGISTER_N_N,                                        // 0b0010100010
    CMPLT32_MEMORY_REGISTER_N_F,                                        // 0b0010100011
    CMPLT32_MEMORY_MEMORY_N_N,                                          // 0b0010100100
    CMPLT32_MEMORY_MEMORY_N_F,                                          // 0b0010100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT32_MEMORY_REGISTER_F_N,                                        // 0b0010101010
    CMPLT32_MEMORY_MEMORY_F_F,                                          // 0b0010101011
    CMPLT32_MEMORY_MEMORY_N_N,                                          // 0b0010101100
    CMPLT32_MEMORY_MEMORY_F_F,                                          // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT64_NUM_REGISTER_N,                                             // 0b0100001010
    CMPLT64_NUM_REGISTER_F,                                             // 0b0100001011
    CMPLT64_NUM_MEMORY_N,                                               // 0b0100001100
    CMPLT64_NUM_MEMORY_F,                                               // 0b0100001101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT64_REGISTER_REGISTER_N_N,                                      // 0b0100010010
    CMPLT64_REGISTER_REGISTER_N_F,                                      // 0b0100010011
    CMPLT64_REGISTER_MEMORY_N_N,                                        // 0b0100010100
    CMPLT64_REGISTER_MEMORY_N_F,                                        // 0b0100010101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT64_REGISTER_REGISTER_F_N,                                      // 0b0100011010
    CMPLT64_REGISTER_REGISTER_F_F,                                      // 0b0100011011
    CMPLT64_REGISTER_MEMORY_F_N,                                        // 0b0100011100
    CMPLT64_REGISTER_MEMORY_F_F,                                        // 0b0100011101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT64_MEMORY_REGISTER_N_N,                                        // 0b0100100010
    CMPLT64_MEMORY_REGISTER_N_F,                                        // 0b0100100011
    CMPLT64_MEMORY_MEMORY_N_N,                                          // 0b0100100100
    CMPLT64_MEMORY_MEMORY_N_F,                                          // 0b0100100101
    NULL,
    NULL,
    NULL,
    NULL,
    CMPLT64_MEMORY_REGISTER_F_N,                                        // 0b0100101010
    CMPLT64_MEMORY_MEMORY_F_F,                                          // 0b0100101011
    CMPLT64_MEMORY_MEMORY_N_N,                                          // 0b0100101100
    CMPLT64_MEMORY_MEMORY_F_F,                                          // 0b0100101101
};



bool CMPLT_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (CMPLT_MODES[Mode]) ? CMPLT_MODES[Mode](PASS_ARGUMENTS) : false;
}