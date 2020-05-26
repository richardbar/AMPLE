#ifndef __AMPLE_METADATA_H__
#define __AMPLE_METADATA_H__

#include "Library.h"
#include <cstdio>
#include <map>
#include <string>
#include <vector>

void LoadMetaData(FILE*& fptr, std::map<int, std::pair<Library*, std::map<int, void*>>>& libs, std::map<std::string, std::string>& settings);

#endif//__AMPLE_METADATA_H__
