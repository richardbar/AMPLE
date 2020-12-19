#pragma once

#include <map>

#include "../../Runtime/include/AMPLE.h"



template <typename T, typename U>
INLINE bool MapHasKey(std::map<T, U> mp, T key)
{
    typename std::map<T, U>::iterator it = mp.find(key);
    return it != mp.end();
}