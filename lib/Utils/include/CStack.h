#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "../../../Runtime/include/AMPLE.h"

typedef struct
{
    uint32_t size;
    void** ptrs;
    uint32_t top;
} StackP;

#define CStack void*

CStack InitializeStack();

bool InsertElementToStack(CStack stack, void* element);
bool RemoveElementFromStack(CStack stack);

void* GetElementFromStack(CStack stack);
INLINE void* FastGetElementFromStack(CStack stack)
{
    return ((StackP*)stack)->ptrs[((StackP*)stack)->top - 1];
}

void FreeStack(CStack stack);


#ifdef __cplusplus
}
#endif