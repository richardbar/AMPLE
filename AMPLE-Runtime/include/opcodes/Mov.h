#ifndef __AMPLE_PROGRAM_ADD_OPCODE_H__
#define __AMPLE_PROGRAM_ADD_OPCODE_H__

#include "Memory.h"

#ifdef __cplusplus
extern "C" {
#endif

_Bool MovOP(uint32_t mode, uint64_t arg1, uint64_t arg2, uint64_t arg3, Memory* memory, Memory* registers, uint32_t* programCounter);

#ifdef __cplusplus
};
#endif

#endif//__AMPLE_PROGRAM_ADD_OPCODE_H__