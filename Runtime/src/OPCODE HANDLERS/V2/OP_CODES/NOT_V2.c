#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "OPCODE HANDLERS/V2.h"



static uint32_t sizeOfRegisters = 0;
#define CHECK_SIZE_OF_REGISTER() if (!sizeOfRegisters) sizeOfRegisters = GetSizeFromList(Registers)
#define CHECK_SIZE_OF_MEMORY() uint32_t sizeOfMemory = GetSizeFromList(Memory)



ASSIGNMENT_FUNCS(NOT, 8, int8_t, = ~)
ASSIGNMENT_FUNCS(NOT, 16, int16_t, = ~)
ASSIGNMENT_FUNCS(NOT, 32, int32_t, = ~)
ASSIGNMENT_FUNCS(NOT, 64, int64_t, = ~)



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
    NOT8_NUM_REGISTER_N,                                                // 0b0000010001
    NOT8_REGISTER_REGISTER_N_N,                                         // 0b0000010010
    NOT8_REGISTER_REGISTER_F_N,                                         // 0b0000010011
    NOT8_MEMORY_REGISTER_N_N,                                           // 0b0000010100
    NOT8_MEMORY_REGISTER_F_N,                                           // 0b0000010101
    NULL,
    NULL,
    NULL,
    NOT8_NUM_REGISTER_F,                                                // 0b0000011001
    NOT8_REGISTER_REGISTER_N_F,                                         // 0b0000011010
    NOT8_REGISTER_REGISTER_F_F,                                         // 0b0000011011
    NOT8_MEMORY_REGISTER_N_F,                                           // 0b0000011100
    NOT8_MEMORY_REGISTER_F_F,                                           // 0b0000011101
    NULL,
    NULL,
    NULL,
    NOT8_NUM_MEMORY_N,                                                  // 0b0000100001
    NOT8_REGISTER_MEMORY_N_N,                                           // 0b0000100010
    NOT8_REGISTER_MEMORY_F_N,                                           // 0b0000100011
    NOT8_MEMORY_MEMORY_N_N,                                             // 0b0000100100
    NOT8_MEMORY_MEMORY_F_N,                                             // 0b0000100101
    NULL,
    NULL,
    NULL,
    NOT8_NUM_MEMORY_F,                                                  // 0b0000101001
    NOT8_REGISTER_MEMORY_N_F,                                           // 0b0000101000
    NOT8_REGISTER_MEMORY_F_F,                                           // 0b0000101011
    NOT8_MEMORY_MEMORY_N_F,                                             // 0b0000101100
    NOT8_MEMORY_MEMORY_F_F,                                             // 0b0000101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NOT16_NUM_REGISTER_N,                                               // 0b0001010001
    NOT16_REGISTER_REGISTER_N_N,                                        // 0b0001010010
    NOT16_REGISTER_REGISTER_F_N,                                        // 0b0001010011
    NOT16_MEMORY_REGISTER_N_N,                                          // 0b0001010100
    NOT16_MEMORY_REGISTER_F_N,                                          // 0b0001010101
    NULL,
    NULL,
    NULL,
    NOT16_NUM_REGISTER_F,                                               // 0b0001011001
    NOT16_REGISTER_REGISTER_N_F,                                        // 0b0001011010
    NOT16_REGISTER_REGISTER_F_F,                                        // 0b0001011011
    NOT16_MEMORY_REGISTER_N_F,                                          // 0b0001011100
    NOT16_MEMORY_REGISTER_F_F,                                          // 0b0001011101
    NULL,
    NULL,
    NULL,
    NOT16_NUM_MEMORY_N,                                                 // 0b0001100001
    NOT16_REGISTER_MEMORY_N_N,                                          // 0b0001100010
    NOT16_REGISTER_MEMORY_F_N,                                          // 0b0001100011
    NOT16_MEMORY_MEMORY_N_N,                                            // 0b0001100100
    NOT16_MEMORY_MEMORY_F_N,                                            // 0b0001100101
    NULL,
    NULL,
    NULL,
    NOT16_NUM_MEMORY_F,                                                 // 0b0001101001
    NOT16_REGISTER_MEMORY_N_F,                                          // 0b0001101000
    NOT16_REGISTER_MEMORY_F_F,                                          // 0b0001101011
    NOT16_MEMORY_MEMORY_N_F,                                            // 0b0001101100
    NOT16_MEMORY_MEMORY_F_F,                                            // 0b0001101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NOT32_NUM_REGISTER_N,                                               // 0b0010010001
    NOT32_REGISTER_REGISTER_N_N,                                        // 0b0010010010
    NOT32_REGISTER_REGISTER_F_N,                                        // 0b0010010011
    NOT32_MEMORY_REGISTER_N_N,                                          // 0b0010010100
    NOT32_MEMORY_REGISTER_F_N,                                          // 0b0010010101
    NULL,
    NULL,
    NULL,
    NOT32_NUM_REGISTER_F,                                               // 0b0010011001
    NOT32_REGISTER_REGISTER_N_F,                                        // 0b0010011010
    NOT32_REGISTER_REGISTER_F_F,                                        // 0b0010011011
    NOT32_MEMORY_REGISTER_N_F,                                          // 0b0010011100
    NOT32_MEMORY_REGISTER_F_F,                                          // 0b0010011101
    NULL,
    NULL,
    NULL,
    NOT32_NUM_MEMORY_N,                                                 // 0b0010100001
    NOT32_REGISTER_MEMORY_N_N,                                          // 0b0010100010
    NOT32_REGISTER_MEMORY_F_N,                                          // 0b0010100011
    NOT32_MEMORY_MEMORY_N_N,                                            // 0b0010100100
    NOT32_MEMORY_MEMORY_F_N,                                            // 0b0010100101
    NULL,
    NULL,
    NULL,
    NOT32_NUM_MEMORY_F,                                                 // 0b0010101001
    NOT32_REGISTER_MEMORY_N_F,                                          // 0b0010101000
    NOT32_REGISTER_MEMORY_F_F,                                          // 0b0010101011
    NOT32_MEMORY_MEMORY_N_F,                                            // 0b0010101100
    NOT32_MEMORY_MEMORY_F_F,                                            // 0b0010101101
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NOT64_NUM_REGISTER_N,                                               // 0b0100010001
    NOT64_REGISTER_REGISTER_N_N,                                        // 0b0100010010
    NOT64_REGISTER_REGISTER_F_N,                                        // 0b0100010011
    NOT64_MEMORY_REGISTER_N_N,                                          // 0b0100010100
    NOT64_MEMORY_REGISTER_F_N,                                          // 0b0100010101
    NULL,
    NULL,
    NULL,
    NOT64_NUM_REGISTER_F,                                               // 0b0100011001
    NOT64_REGISTER_REGISTER_N_F,                                        // 0b0100011010
    NOT64_REGISTER_REGISTER_F_F,                                        // 0b0100011011
    NOT64_MEMORY_REGISTER_N_F,                                          // 0b0100011100
    NOT64_MEMORY_REGISTER_F_F,                                          // 0b0100011101
    NULL,
    NULL,
    NULL,
    NOT64_NUM_MEMORY_N,                                                 // 0b0100100001
    NOT64_REGISTER_MEMORY_N_N,                                          // 0b0100100010
    NOT64_REGISTER_MEMORY_F_N,                                          // 0b0100100011
    NOT64_MEMORY_MEMORY_N_N,                                            // 0b0100100100
    NOT64_MEMORY_MEMORY_F_N,                                            // 0b0100100101
    NULL,
    NULL,
    NULL,
    NOT64_NUM_MEMORY_F,                                                 // 0b0100101001
    NOT64_REGISTER_MEMORY_N_F,                                          // 0b0100101000
    NOT64_REGISTER_MEMORY_F_F,                                          // 0b0100101011
    NOT64_MEMORY_MEMORY_N_F,                                            // 0b0100101100
    NOT64_MEMORY_MEMORY_F_F                                             // 0b0100101101
};



bool NOT_V2(MODE_FUNCTION_ARGUMENTS)
{
    return (OR_MODES[Mode]) ? OR_MODES[Mode](PASS_ARGUMENTS) : false;
}