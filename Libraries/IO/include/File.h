#ifndef __AMPLE_LIBRARY_FILE_H__
#define __AMPLE_LIBRARY_FILE_H__

#include "AMPLE.h"
#include "FileMode.h"

#include <cstdio>
#include <string>

class File {
public:
    EXPORT static void Close(FILE* fptr);

    EXPORT static void Copy(std::string& src, std::string& dest);
    EXPORT static void Copy(const char* src, const char* dest);
    EXPORT static void Copy(std::string& src, std::string& dest, bool overwrite);
    EXPORT static void Copy(const char* src, const char* dest, bool overwrite);

    EXPORT static void Create(std::string& fileName);
    EXPORT static void Create(const char* fileName);

    EXPORT static void Delete(std::string& fileName);
    EXPORT static void Delete(const char* fileName);

    EXPORT static bool Exists(std::string& fileName);
    EXPORT static bool Exists(const char* fileName);

    EXPORT static void Move(std::string& src, std::string& dest);
    EXPORT static void Move(const char* src, const char* dest);
    EXPORT static void Move(std::string& src, std::string& dest, bool overwrite);
    EXPORT static void Move(const char* src, const char* dest, bool overwrite);

    EXPORT static FILE* Open(std::string& fileName, FileMode fileMode);
    EXPORT static FILE* Open(const char* fileName, FileMode fileMode);
};

#endif//__AMPLE_LIBRARY_FILE_H__
