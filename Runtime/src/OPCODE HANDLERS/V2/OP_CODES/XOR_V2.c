#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(XOR, 8, int8_t, ^=)
ASSIGNMENT_FUNCS(XOR, 16, int16_t, ^=)
ASSIGNMENT_FUNCS(XOR, 32, int32_t, ^=)
ASSIGNMENT_FUNCS(XOR, 64, int64_t, ^=)



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
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    XOR8_NUM_REGISTER_N,                                                // 0b0000010001
    XOR8_REGISTER_REGISTER_N_N,                                         // 0b0000010010
    XOR8_REGISTER_REGISTER_F_N,                                         // 0b0000010011
    XOR8_MEMORY_REGISTER_N_N,                                           // 0b0000010100
    XOR8_MEMORY_REGISTER_F_N,                                           // 0b0000010101
    NULL,
    NULL,
    NULL,
    XOR8_NUM_REGISTER_F,                                                // 0b0000011001
    XOR8_REGISTER_REGISTER_N_F,                                         // 0b0000011010
    XOR8_REGISTER_REGISTER_F_F,                                         // 0b0000011011
    XOR8_MEMORY_REGISTER_N_F,                                           // 0b0000011100
    XOR8_MEMORY_REGISTER_F_F,                                           // 0b0000011101
    NULL,
    NULL,
    NULL,
    XOR8_NUM_MEMORY_N,                                                  // 0b0000100001
    XOR8_REGISTER_MEMORY_N_N,                                           // 0b0000100010
    XOR8_REGISTER_MEMORY_F_N,                                           // 0b0000100011
    XOR8_MEMORY_MEMORY_N_N,                                             // 0b0000100100
    XOR8_MEMORY_MEMORY_F_N,                                             // 0b0000100101
    NULL,
    NULL,
    NULL,
    XOR8_NUM_MEMORY_F,                                                  // 0b0000101001
    XOR8_REGISTER_MEMORY_N_F,                                           // 0b0000101000
    XOR8_REGISTER_MEMORY_F_F,                                           // 0b0000101011
    XOR8_MEMORY_MEMORY_N_F,                                             // 0b0000101100
    XOR8_MEMORY_MEMORY_F_F,                                             // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    XOR16_NUM_REGISTER_N,                                               // 0b0001010001
    XOR16_REGISTER_REGISTER_N_N,                                        // 0b0001010010
    XOR16_REGISTER_REGISTER_F_N,                                        // 0b0001010011
    XOR16_MEMORY_REGISTER_N_N,                                          // 0b0001010100
    XOR16_MEMORY_REGISTER_F_N,                                          // 0b0001010101
    NULL,
    NULL,
    NULL,
    XOR16_NUM_REGISTER_F,                                               // 0b0001011001
    XOR16_REGISTER_REGISTER_N_F,                                        // 0b0001011010
    XOR16_REGISTER_REGISTER_F_F,                                        // 0b0001011011
    XOR16_MEMORY_REGISTER_N_F,                                          // 0b0001011100
    XOR16_MEMORY_REGISTER_F_F,                                          // 0b0001011101
    NULL,
    NULL,
    NULL,
    XOR16_NUM_MEMORY_N,                                                 // 0b0001100001
    XOR16_REGISTER_MEMORY_N_N,                                          // 0b0001100010
    XOR16_REGISTER_MEMORY_F_N,                                          // 0b0001100011
    XOR16_MEMORY_MEMORY_N_N,                                            // 0b0001100100
    XOR16_MEMORY_MEMORY_F_N,                                            // 0b0001100101
    NULL,
    NULL,
    NULL,
    XOR16_NUM_MEMORY_F,                                                 // 0b0001101001
    XOR16_REGISTER_MEMORY_N_F,                                          // 0b0001101000
    XOR16_REGISTER_MEMORY_F_F,                                          // 0b0001101011
    XOR16_MEMORY_MEMORY_N_F,                                            // 0b0001101100
    XOR16_MEMORY_MEMORY_F_F,                                            // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    XOR32_NUM_REGISTER_N,                                               // 0b0010010001
    XOR32_REGISTER_REGISTER_N_N,                                        // 0b0010010010
    XOR32_REGISTER_REGISTER_F_N,                                        // 0b0010010011
    XOR32_MEMORY_REGISTER_N_N,                                          // 0b0010010100
    XOR32_MEMORY_REGISTER_F_N,                                          // 0b0010010101
    NULL,
    NULL,
    NULL,
    XOR32_NUM_REGISTER_F,                                               // 0b0010011001
    XOR32_REGISTER_REGISTER_N_F,                                        // 0b0010011010
    XOR32_REGISTER_REGISTER_F_F,                                        // 0b0010011011
    XOR32_MEMORY_REGISTER_N_F,                                          // 0b0010011100
    XOR32_MEMORY_REGISTER_F_F,                                          // 0b0010011101
    NULL,
    NULL,
    NULL,
    XOR32_NUM_MEMORY_N,                                                 // 0b0010100001
    XOR32_REGISTER_MEMORY_N_N,                                          // 0b0010100010
    XOR32_REGISTER_MEMORY_F_N,                                          // 0b0010100011
    XOR32_MEMORY_MEMORY_N_N,                                            // 0b0010100100
    XOR32_MEMORY_MEMORY_F_N,                                            // 0b0010100101
    NULL,
    NULL,
    NULL,
    XOR32_NUM_MEMORY_F,                                                 // 0b0010101001
    XOR32_REGISTER_MEMORY_N_F,                                          // 0b0010101000
    XOR32_REGISTER_MEMORY_F_F,                                          // 0b0010101011
    XOR32_MEMORY_MEMORY_N_F,                                            // 0b0010101100
    XOR32_MEMORY_MEMORY_F_F,                                            // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    XOR64_NUM_REGISTER_N,                                               // 0b0100010001
    XOR64_REGISTER_REGISTER_N_N,                                        // 0b0100010010
    XOR64_REGISTER_REGISTER_F_N,                                        // 0b0100010011
    XOR64_MEMORY_REGISTER_N_N,                                          // 0b0100010100
    XOR64_MEMORY_REGISTER_F_N,                                          // 0b0100010101
    NULL,
    NULL,
    NULL,
    XOR64_NUM_REGISTER_F,                                               // 0b0100011001
    XOR64_REGISTER_REGISTER_N_F,                                        // 0b0100011010
    XOR64_REGISTER_REGISTER_F_F,                                        // 0b0100011011
    XOR64_MEMORY_REGISTER_N_F,                                          // 0b0100011100
    XOR64_MEMORY_REGISTER_F_F,                                          // 0b0100011101
    NULL,
    NULL,
    NULL,
    XOR64_NUM_MEMORY_N,                                                 // 0b0100100001
    XOR64_REGISTER_MEMORY_N_N,                                          // 0b0100100010
    XOR64_REGISTER_MEMORY_F_N,                                          // 0b0100100011
    XOR64_MEMORY_MEMORY_N_N,                                            // 0b0100100100
    XOR64_MEMORY_MEMORY_F_N,                                            // 0b0100100101
    NULL,
    NULL,
    NULL,
    XOR64_NUM_MEMORY_F,                                                 // 0b0100101001
    XOR64_REGISTER_MEMORY_N_F,                                          // 0b0100101000
    XOR64_REGISTER_MEMORY_F_F,                                          // 0b0100101011
    XOR64_MEMORY_MEMORY_N_F,                                            // 0b0100101100
    XOR64_MEMORY_MEMORY_F_F                                             // 0b0100101101
};



bool XOR_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (OR_MODES[Mode]) ? OR_MODES[Mode](PASS_ARGUMENTS) : false;
}