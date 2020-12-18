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
    void** ptrs;
    uint32_t size;
    uint32_t used;
    bool initialized;
    bool capacityLocked;
} ListP;

#define CList void*

CList InitializeList(uint32_t initialSize);

bool InsertElementToList(CList list, void* element);

void* GetElementFromList(CList list, uint32_t position);
INLINE void* FastGetElementFromList(CList list, uint32_t position)
{
    if (((ListP*)list)->used <= position)
        return NULL;

    return (((ListP*)list)->ptrs)[position];
}

bool ResizeList(CList list, uint32_t newSize);

uint32_t GetCapacityFromList(CList list);
uint32_t GetSizeFromList(CList list);

bool ContainsValueInList(CList list, void* element, bool (*comparer)(void*, void*));

void LockCapacityList(CList list);

void FreeList(CList list);

#ifdef __cplusplus
}
#endif