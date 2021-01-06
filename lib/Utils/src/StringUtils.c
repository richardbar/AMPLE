#include "StringUtils.h"

#include <string.h>


bool StringEqual(void* str1, void* str2)
{
    return strcmp((const char*)str1, (const char*)str2) == 0;
}