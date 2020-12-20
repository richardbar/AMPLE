#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(ADD, 8, int8_t, +=)
ASSIGNMENT_FUNCS(ADD, 16, int16_t, +=)
ASSIGNMENT_FUNCS(ADD, 32, int32_t, +=)
ASSIGNMENT_FUNCS(ADD, 64, int64_t, +=)



static bool (*ADD_MODES[])(ARGUMENT_TYPES) = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ADD8_NUM_REGISTER_N,                                                // 0b0000010001
    ADD8_REGISTER_REGISTER_N_N,                                         // 0b0000010010
    ADD8_REGISTER_REGISTER_F_N,                                         // 0b0000010011
    ADD8_MEMORY_REGISTER_N_N,                                           // 0b0000010100
    ADD8_MEMORY_REGISTER_F_N,                                           // 0b0000010101
    NULL,
    NULL,
    NULL,
    ADD8_NUM_REGISTER_F,                                                // 0b0000011001
    ADD8_REGISTER_REGISTER_N_F,                                         // 0b0000011010
    ADD8_REGISTER_REGISTER_F_F,                                         // 0b0000011011
    ADD8_MEMORY_REGISTER_N_F,                                           // 0b0000011100
    ADD8_MEMORY_REGISTER_F_F,                                           // 0b0000011101
    NULL,
    NULL,
    NULL,
    ADD8_NUM_MEMORY_N,                                                  // 0b0000100001
    ADD8_REGISTER_MEMORY_N_N,                                           // 0b0000100010
    ADD8_REGISTER_MEMORY_F_N,                                           // 0b0000100011
    ADD8_MEMORY_MEMORY_N_N,                                             // 0b0000100100
    ADD8_MEMORY_MEMORY_F_N,                                             // 0b0000100101
    NULL,
    NULL,
    NULL,
    ADD8_NUM_MEMORY_F,                                                  // 0b0000101001
    ADD8_REGISTER_MEMORY_N_F,                                           // 0b0000101000
    ADD8_REGISTER_MEMORY_F_F,                                           // 0b0000101011
    ADD8_MEMORY_MEMORY_N_F,                                             // 0b0000101100
    ADD8_MEMORY_MEMORY_F_F,                                             // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ADD16_NUM_REGISTER_N,                                               // 0b0001010001
    ADD16_REGISTER_REGISTER_N_N,                                        // 0b0001010010
    ADD16_REGISTER_REGISTER_F_N,                                        // 0b0001010011
    ADD16_MEMORY_REGISTER_N_N,                                          // 0b0001010100
    ADD16_MEMORY_REGISTER_F_N,                                          // 0b0001010101
    NULL,
    NULL,
    NULL,
    ADD16_NUM_REGISTER_F,                                               // 0b0001011001
    ADD16_REGISTER_REGISTER_N_F,                                        // 0b0001011010
    ADD16_REGISTER_REGISTER_F_F,                                        // 0b0001011011
    ADD16_MEMORY_REGISTER_N_F,                                          // 0b0001011100
    ADD16_MEMORY_REGISTER_F_F,                                          // 0b0001011101
    NULL,
    NULL,
    NULL,
    ADD16_NUM_MEMORY_N,                                                 // 0b0001100001
    ADD16_REGISTER_MEMORY_N_N,                                          // 0b0001100010
    ADD16_REGISTER_MEMORY_F_N,                                          // 0b0001100011
    ADD16_MEMORY_MEMORY_N_N,                                            // 0b0001100100
    ADD16_MEMORY_MEMORY_F_N,                                            // 0b0001100101
    NULL,
    NULL,
    NULL,
    ADD16_NUM_MEMORY_F,                                                 // 0b0001101001
    ADD16_REGISTER_MEMORY_N_F,                                          // 0b0001101000
    ADD16_REGISTER_MEMORY_F_F,                                          // 0b0001101011
    ADD16_MEMORY_MEMORY_N_F,                                            // 0b0001101100
    ADD16_MEMORY_MEMORY_F_F,                                            // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ADD32_NUM_REGISTER_N,                                               // 0b0010010001
    ADD32_REGISTER_REGISTER_N_N,                                        // 0b0010010010
    ADD32_REGISTER_REGISTER_F_N,                                        // 0b0010010011
    ADD32_MEMORY_REGISTER_N_N,                                          // 0b0010010100
    ADD32_MEMORY_REGISTER_F_N,                                          // 0b0010010101
    NULL,
    NULL,
    NULL,
    ADD32_NUM_REGISTER_F,                                               // 0b0010011001
    ADD32_REGISTER_REGISTER_N_F,                                        // 0b0010011010
    ADD32_REGISTER_REGISTER_F_F,                                        // 0b0010011011
    ADD32_MEMORY_REGISTER_N_F,                                          // 0b0010011100
    ADD32_MEMORY_REGISTER_F_F,                                          // 0b0010011101
    NULL,
    NULL,
    NULL,
    ADD32_NUM_MEMORY_N,                                                 // 0b0010100001
    ADD32_REGISTER_MEMORY_N_N,                                          // 0b0010100010
    ADD32_REGISTER_MEMORY_F_N,                                          // 0b0010100011
    ADD32_MEMORY_MEMORY_N_N,                                            // 0b0010100100
    ADD32_MEMORY_MEMORY_F_N,                                            // 0b0010100101
    NULL,
    NULL,
    NULL,
    ADD32_NUM_MEMORY_F,                                                 // 0b0010101001
    ADD32_REGISTER_MEMORY_N_F,                                          // 0b0010101000
    ADD32_REGISTER_MEMORY_F_F,                                          // 0b0010101011
    ADD32_MEMORY_MEMORY_N_F,                                            // 0b0010101100
    ADD32_MEMORY_MEMORY_F_F,                                            // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ADD64_NUM_REGISTER_N,                                               // 0b0100010001
    ADD64_REGISTER_REGISTER_N_N,                                        // 0b0100010010
    ADD64_REGISTER_REGISTER_F_N,                                        // 0b0100010011
    ADD64_MEMORY_REGISTER_N_N,                                          // 0b0100010100
    ADD64_MEMORY_REGISTER_F_N,                                          // 0b0100010101
    NULL,
    NULL,
    NULL,
    ADD64_NUM_REGISTER_F,                                               // 0b0100011001
    ADD64_REGISTER_REGISTER_N_F,                                        // 0b0100011010
    ADD64_REGISTER_REGISTER_F_F,                                        // 0b0100011011
    ADD64_MEMORY_REGISTER_N_F,                                          // 0b0100011100
    ADD64_MEMORY_REGISTER_F_F,                                          // 0b0100011101
    NULL,
    NULL,
    NULL,
    ADD64_NUM_MEMORY_N,                                                 // 0b0100100001
    ADD64_REGISTER_MEMORY_N_N,                                          // 0b0100100010
    ADD64_REGISTER_MEMORY_F_N,                                          // 0b0100100011
    ADD64_MEMORY_MEMORY_N_N,                                            // 0b0100100100
    ADD64_MEMORY_MEMORY_F_N,                                            // 0b0100100101
    NULL,
    NULL,
    NULL,
    ADD64_NUM_MEMORY_F,                                                 // 0b0100101001
    ADD64_REGISTER_MEMORY_N_F,                                          // 0b0100101000
    ADD64_REGISTER_MEMORY_F_F,                                          // 0b0100101011
    ADD64_MEMORY_MEMORY_N_F,                                            // 0b0100101100
    ADD64_MEMORY_MEMORY_F_F                                             // 0b0100101101
};



bool ADD_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (ADD_MODES[Mode]) ? ADD_MODES[Mode](PASS_ARGUMENTS) : false;
}