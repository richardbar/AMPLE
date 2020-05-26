#include "File.h"

#include <fstream>

#if defined(__WINDOWS__)
    #include <Windows.h>
#elif defined(__LINUX__) || defined(__APPLE__)
#include <cerrno>
    #include <cassert>
    #include <sys/errno.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <cstdio>
#endif

#if defined(__LINUX__) || defined(__APPLE__)
error_t fopen_s(FILE** f, const char* name, const char* mode) {
    error_t ret = 0;
    assert(f);
    *f = fopen(name, mode);
    if (!*f)
        ret = errno;
    return ret;
}
#endif

void File::Close(FILE* fptr) {
    fclose(fptr);
}

void File::Copy(std::string& src, std::string& dest)
{
    Copy(src.c_str(), dest.c_str(), false);
}

void File::Copy(const char* src, const char* dest)
{
    Copy(src, dest, false);
}

void File::Copy(std::string& src, std::string& dest, bool overwrite)
{
    Copy(src.c_str(), dest.c_str(), overwrite);
}

void File::Copy(const char* src, const char* dest, bool overwrite)
{
#if defined(__WINDOWS__)
    bool check = CopyFile(src, dest, !overwrite);
    printf("%s\n", check ? "true" : "false");
#elif defined(__LINUX__) || defined(__APPLE)
    if (Exists(dest) && !overwrite) return;
    FILE* source;
    FILE* destination;

    fopen_s(&source, src, "r");
    fopen_s(&destination, dest, "w");

    char buf[BUFSIZ];
    size_t size;

    while ((size = fread(buf, 1, BUFSIZ, source)))
        fwrite(buf, 1, size, destination);

    fclose(source);
    fclose(destination);
#endif
}

void File::Create(std::string& fileName)
{
    Create(fileName.c_str());
}

void File::Create(const char* fileName)
{
    std::ofstream f(fileName);
}

bool File::Exists(std::string& fileName)
{
    return Exists(fileName.c_str());
}

bool File::Exists(const char* fileName) {
    FILE* fptr;
    fopen_s(&fptr, fileName, "r");
    if (fptr)
    {
        fclose(fptr);
        return true;
    }
    return false;
}

FILE* File::Open(std::string& fileName, FileMode fileMode)
{
    return Open(fileName.c_str(), fileMode);
}

FILE *File::Open(const char *fileName, FileMode fileMode) {
    FILE* fptr = nullptr;
    if ((fileMode & FileMode::Read) == FileMode::Read && (fileMode & FileMode::Write) == FileMode::Write)
        fopen_s(&fptr, fileName, (fileMode & FileMode::Append) == FileMode::Append ? "a+" : "w+");
    else if ((fileMode & FileMode::Write) == FileMode::Write)
        fopen_s(&fptr, fileName, (fileMode & FileMode::Append) == FileMode::Append ? "a" : "w");
    else if ((fileMode & FileMode::Read) == FileMode::Read)
        fopen_s(&fptr, fileName, "r");
    return fptr;
}