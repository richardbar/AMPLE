#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)


COMPARISON_FUNCS(GE, 8, int8_t, >=)
COMPARISON_FUNCS(GE, 16, int16_t, >=)
COMPARISON_FUNCS(GE, 32, int32_t, >=)
COMPARISON_FUNCS(GE, 64, int64_t, >=)



static bool (*CMPGE_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGE8_NUM_REGISTER_N,                                                // 0b0000010001
    CMPGE8_REGISTER_REGISTER_N_N,                                         // 0b0000010010
    CMPGE8_REGISTER_REGISTER_F_N,                                         // 0b0000010011
    CMPGE8_MEMORY_REGISTER_N_N,                                           // 0b0000010100
    CMPGE8_MEMORY_REGISTER_F_N,                                           // 0b0000010101
    NULL,
    NULL,
    NULL,
    CMPGE8_NUM_REGISTER_F,                                                // 0b0000011001
    CMPGE8_REGISTER_REGISTER_N_F,                                         // 0b0000011010
    CMPGE8_REGISTER_REGISTER_F_F,                                         // 0b0000011011
    CMPGE8_MEMORY_REGISTER_N_F,                                           // 0b0000011100
    CMPGE8_MEMORY_REGISTER_F_F,                                           // 0b0000011101
    NULL,
    NULL,
    NULL,
    CMPGE8_NUM_MEMORY_N,                                                  // 0b0000100001
    CMPGE8_REGISTER_MEMORY_N_N,                                           // 0b0000100010
    CMPGE8_REGISTER_MEMORY_F_N,                                           // 0b0000100011
    CMPGE8_MEMORY_MEMORY_N_N,                                             // 0b0000100100
    CMPGE8_MEMORY_MEMORY_F_N,                                             // 0b0000100101
    NULL,
    NULL,
    NULL,
    CMPGE8_NUM_MEMORY_F,                                                  // 0b0000101001
    CMPGE8_REGISTER_MEMORY_N_F,                                           // 0b0000101000
    CMPGE8_REGISTER_MEMORY_F_F,                                           // 0b0000101011
    CMPGE8_MEMORY_MEMORY_N_F,                                             // 0b0000101100
    CMPGE8_MEMORY_MEMORY_F_F,                                             // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGE16_NUM_REGISTER_N,                                               // 0b0001010001
    CMPGE16_REGISTER_REGISTER_N_N,                                        // 0b0001010010
    CMPGE16_REGISTER_REGISTER_F_N,                                        // 0b0001010011
    CMPGE16_MEMORY_REGISTER_N_N,                                          // 0b0001010100
    CMPGE16_MEMORY_REGISTER_F_N,                                          // 0b0001010101
    NULL,
    NULL,
    NULL,
    CMPGE16_NUM_REGISTER_F,                                               // 0b0001011001
    CMPGE16_REGISTER_REGISTER_N_F,                                        // 0b0001011010
    CMPGE16_REGISTER_REGISTER_F_F,                                        // 0b0001011011
    CMPGE16_MEMORY_REGISTER_N_F,                                          // 0b0001011100
    CMPGE16_MEMORY_REGISTER_F_F,                                          // 0b0001011101
    NULL,
    NULL,
    NULL,
    CMPGE16_NUM_MEMORY_N,                                                 // 0b0001100001
    CMPGE16_REGISTER_MEMORY_N_N,                                          // 0b0001100010
    CMPGE16_REGISTER_MEMORY_F_N,                                          // 0b0001100011
    CMPGE16_MEMORY_MEMORY_N_N,                                            // 0b0001100100
    CMPGE16_MEMORY_MEMORY_F_N,                                            // 0b0001100101
    NULL,
    NULL,
    NULL,
    CMPGE16_NUM_MEMORY_F,                                                 // 0b0001101001
    CMPGE16_REGISTER_MEMORY_N_F,                                          // 0b0001101000
    CMPGE16_REGISTER_MEMORY_F_F,                                          // 0b0001101011
    CMPGE16_MEMORY_MEMORY_N_F,                                            // 0b0001101100
    CMPGE16_MEMORY_MEMORY_F_F,                                            // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGE32_NUM_REGISTER_N,                                               // 0b0010010001
    CMPGE32_REGISTER_REGISTER_N_N,                                        // 0b0010010010
    CMPGE32_REGISTER_REGISTER_F_N,                                        // 0b0010010011
    CMPGE32_MEMORY_REGISTER_N_N,                                          // 0b0010010100
    CMPGE32_MEMORY_REGISTER_F_N,                                          // 0b0010010101
    NULL,
    NULL,
    NULL,
    CMPGE32_NUM_REGISTER_F,                                               // 0b0010011001
    CMPGE32_REGISTER_REGISTER_N_F,                                        // 0b0010011010
    CMPGE32_REGISTER_REGISTER_F_F,                                        // 0b0010011011
    CMPGE32_MEMORY_REGISTER_N_F,                                          // 0b0010011100
    CMPGE32_MEMORY_REGISTER_F_F,                                          // 0b0010011101
    NULL,
    NULL,
    NULL,
    CMPGE32_NUM_MEMORY_N,                                                 // 0b0010100001
    CMPGE32_REGISTER_MEMORY_N_N,                                          // 0b0010100010
    CMPGE32_REGISTER_MEMORY_F_N,                                          // 0b0010100011
    CMPGE32_MEMORY_MEMORY_N_N,                                            // 0b0010100100
    CMPGE32_MEMORY_MEMORY_F_N,                                            // 0b0010100101
    NULL,
    NULL,
    NULL,
    CMPGE32_NUM_MEMORY_F,                                                 // 0b0010101001
    CMPGE32_REGISTER_MEMORY_N_F,                                          // 0b0010101000
    CMPGE32_REGISTER_MEMORY_F_F,                                          // 0b0010101011
    CMPGE32_MEMORY_MEMORY_N_F,                                            // 0b0010101100
    CMPGE32_MEMORY_MEMORY_F_F,                                            // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    CMPGE64_NUM_REGISTER_N,                                               // 0b0100010001
    CMPGE64_REGISTER_REGISTER_N_N,                                        // 0b0100010010
    CMPGE64_REGISTER_REGISTER_F_N,                                        // 0b0100010011
    CMPGE64_MEMORY_REGISTER_N_N,                                          // 0b0100010100
    CMPGE64_MEMORY_REGISTER_F_N,                                          // 0b0100010101
    NULL,
    NULL,
    NULL,
    CMPGE64_NUM_REGISTER_F,                                               // 0b0100011001
    CMPGE64_REGISTER_REGISTER_N_F,                                        // 0b0100011010
    CMPGE64_REGISTER_REGISTER_F_F,                                        // 0b0100011011
    CMPGE64_MEMORY_REGISTER_N_F,                                          // 0b0100011100
    CMPGE64_MEMORY_REGISTER_F_F,                                          // 0b0100011101
    NULL,
    NULL,
    NULL,
    CMPGE64_NUM_MEMORY_N,                                                 // 0b0100100001
    CMPGE64_REGISTER_MEMORY_N_N,                                          // 0b0100100010
    CMPGE64_REGISTER_MEMORY_F_N,                                          // 0b0100100011
    CMPGE64_MEMORY_MEMORY_N_N,                                            // 0b0100100100
    CMPGE64_MEMORY_MEMORY_F_N,                                            // 0b0100100101
    NULL,
    NULL,
    NULL,
    CMPGE64_NUM_MEMORY_F,                                                 // 0b0100101001
    CMPGE64_REGISTER_MEMORY_N_F,                                          // 0b0100101000
    CMPGE64_REGISTER_MEMORY_F_F,                                          // 0b0100101011
    CMPGE64_MEMORY_MEMORY_N_F,                                            // 0b0100101100
    CMPGE64_MEMORY_MEMORY_F_F                                             // 0b0100101101
};



bool CMPGE_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (CMPGE_MODES[Mode]) ? CMPGE_MODES[Mode](PASS_ARGUMENTS) : false;
}