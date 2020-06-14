#include "File.h"

#include "ArgumentNullException.h"
#include "FileNotFoundException.h"
#include <fstream>
#include "IOException.h"
#include "UnauthorizedAccessException.h"

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
    CopyFile(src, dest, !overwrite);
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


void File::Delete(std::string& fileName)
{
    Delete(fileName.c_str());
}

void File::Delete(const char* fileName)
{
    if (!Exists(fileName)) return;
#if defined(__WINDOWS__)
    DeleteFile(fileName);
#elif defined(__LINUX__) || defined(__APPLE__)
    remove(fileName);
#endif
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


void File::Move(std::string& src, std::string& dest)
{
    Move(src.c_str(), dest.c_str(), false);
}

void File::Move(const char* src, const char* dest)
{
    Move(src, dest, false);
}

void File::Move(std::string& src, std::string& dest, bool overwrite)
{
    Move(src.c_str(), dest.c_str(), overwrite);
}

void File::Move(const char* src, const char* dest, bool overwrite)
{
    if (Exists(dest) && !overwrite) return;
#if defined(__WINDOWS__)
    MoveFile(src, dest);
#else
    Copy(src, dest);
    Delete(src);
#endif
}


FILE* File::Open(std::string& fileName, FileMode fileMode)
{
    return Open(fileName.c_str(), fileMode);
}

FILE *File::Open(const char *fileName, FileMode fileMode) {
    if (fileName == nullptr)
        throw ArgumentNullException("File name can not be null");
    FILE* fptr = nullptr;
    const char* mode = nullptr;
    if ((fileMode & FileMode::Binary) != FileMode::Binary)
    {
        if ((fileMode & FileMode::Read) == FileMode::Read && (fileMode & FileMode::Write) == FileMode::Write)
            mode = (fileMode & FileMode::Append) == FileMode::Append ? "ab+" : "wb+";
        else if ((fileMode & FileMode::Write) == FileMode::Write)
            mode = (fileMode & FileMode::Append) == FileMode::Append ? "ab" : "wb";
        else if ((fileMode & FileMode::Read) == FileMode::Read)
            mode = "rb";
    }
    else
    {
        if ((fileMode & FileMode::Read) == FileMode::Read && (fileMode & FileMode::Write) == FileMode::Write)
            mode = (fileMode & FileMode::Append) == FileMode::Append ? "a+" : "w+";
        else if ((fileMode & FileMode::Write) == FileMode::Write)
            mode = (fileMode & FileMode::Append) == FileMode::Append ? "a" : "w";
        else if ((fileMode & FileMode::Read) == FileMode::Read)
            mode = "r";
    }
    fopen_s(&fptr, fileName, mode);
    if (!fptr)
        throw IOException("An I/O exception happened when opening file");
    return fptr;
}
