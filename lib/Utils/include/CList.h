#pragma once

#include <stdint.h>

#define CList void*

CList InitializeList(uint32_t initialSize);
bool InsertElementToList(CList list, void* element);
void* GetElementFromList(CList list, uint32_t position);
bool ResizeList(CList list, uint32_t newSize);
uint32_t GetCapacityFromList(CList list);
uint32_t GetSizeFromList(CList list);
bool ContainsValueInList(CList list, void* element, bool (*comparer)(void*, void*));
void LockCapacityList(CList list);
void FreeList(CList list);