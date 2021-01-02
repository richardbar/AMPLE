#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "../../../Runtime/include/AMPLE.h"

#include "CList.h"

typedef struct
{
    uint32_t size;
    void** ptrs;
    uint32_t top;
} StackP;

#define CStack void*

CStack InitializeStack(uint32_t initialSize);

bool InsertElementToStack(CStack stack, void* element);
bool RemoveElementFromStack(CStack stack);

void* GetElementFromStack(CStack stack);

void FreeStack(CStack stack);


#ifdef __cplusplus
}
#endif