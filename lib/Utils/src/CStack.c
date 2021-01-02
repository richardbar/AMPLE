#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "CStack.h"
#include "CList.h"

CStack InitializeStack(uint32_t initialSize)
{
    if (initialSize == 0)
        initialSize = 1;

    StackP* stackToBeReturned = (StackP*)malloc(sizeof(StackP*));
    if (!stackToBeReturned)
        return NULL;

    stackToBeReturned->ptrs = (void*)malloc(initialSize * sizeof(void*));
    if (!stackToBeReturned->ptrs)
    {
        free(stackToBeReturned);
        return NULL;
    }
    stackToBeReturned->size = initialSize;
    stackToBeReturned->top = 0;
}

bool InsertElementToStack(CStack stack, void* element)
{
    if (!stack)
        return false;

    StackP* stck = (StackP*)stack;
    if (stck->top >= stck->size)
    {
        void** oldPtr = stck->ptrs;
        stck->ptrs = (void**)realloc(stck->ptrs, stck->size * 2 * sizeof(void*));
        if (!stck->ptrs)
        {
            stck->ptrs = oldPtr;
            return false;
        }
        stck->size *= 2;
    }

    stck->ptrs[stck->top++] = element;
    return true;
}

bool RemoveElementFromStack(CStack stack)
{
    if (!stack)
        return false;

    StackP * stck = (StackP*)stack;
    stck->top--;
}

void* GetElementFromStack(CStack stack)
{
    if (!stack)
        return NULL;

    StackP * stck = (StackP*)stack;
    return stck->ptrs[stck->top];
}

void FreeStack(CStack stack)
{
    if (!stack)
        return;

    StackP* stck = (StackP*)stack;
    if (stck->ptrs)
        free(stck->ptrs);
    free(stck);
}
