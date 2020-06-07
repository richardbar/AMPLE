#ifndef __AMPLE_LIBRARY_DIRECTORY_H__
#define __AMPLE_LIBRARY_DIRECTORY_H__

#include "AMPLE.h"

#include <cstdio>
#include <string>

class Directory
{
public:
    //EXPORT static void CreateDirectory(std::string& path);
    //EXPORT static void CreateDirectory(const char* path);

    EXPORT static void Delete(std::string& path);
    EXPORT static void Delete(const char* path);
};

#endif//__AMPLE_LIBRARY_DIRECTORY_H__