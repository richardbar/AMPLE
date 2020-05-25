#ifndef __AMPLE_LIBRARY_FILE_H__
#define __AMPLE_LIBRARY_FILE_H__

#include "AMPLE.h"
#include "FileMode.h"

#include <cstdio>
#include <string>
class File {
public:
    static void Close(FILE* fptr);

    static void Copy(std::string& src, std::string& dest);
    static void Copy(const char* src, const char* dest);
    static void Copy(std::string& src, std::string& dest, bool overwrite);
    static void Copy(const char* src, const char* dest, bool overwrite);

    static void Create(std::string& fileName);
    static void Create(const char* fileName);

    static bool Exists(std::string& fileName);
    static bool Exists(const char* fileName);

    static FILE* Open(std::string& fileName, FileMode fileMode);
    static FILE* Open(const char* fileName, FileMode fileMode);
};

#endif//__AMPLE_LIBRARY_FILE_H__
