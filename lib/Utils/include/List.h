#pragma once

#include <stdint.h>

#define List void*

List InitializeList(uint32_t initialSize);
bool InsertElementToList(List list, void* element);
void* GetElementFromList(List list, uint32_t position);
bool ResizeList(List list, uint32_t newSize);
uint32_t GetCapacityFromList(List list);
uint32_t GetSizeFromList(List list);
bool ContainsValueInList(List list, void* element, bool (*comparer)(void*, void*));
void LockCapacityList(List list);
void FreeList(List list);