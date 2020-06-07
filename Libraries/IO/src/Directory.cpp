#include "Directory.h"

#include "ArgumentException.h"
#include "ArgumentNullException.h"
#include "IOException.h"
#include <cstring>

#if defined(__WINDOWS__)
#include <Windows.h>
#elif defined(__LINUX__) || defined(__APPLE__)
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

/*void Directory::CreateDirectory(std::string& path)
{
    CreateDirectory(path.c_str());
}

void Directory::CreateDirectory(const char *path)
{
    if (strlen(path) == 0)
        throw ArgumentException("Path length can not be 0");
    if (path == nullptr)
        throw ArgumentNullException("Path can not be NULL");
#if defined(__WINDOWS__)
    bool returnVal = CreateDirectoryA(path, NULL);
    if (returnVal) return;
    if (GetLastError() == ERROR_ALREADY_EXISTS)
        throw IOException("Directory already exists");
    else if (GetLastError() == ERROR_PATH_NOT_FOUND)
        throw IOException("One or more intermediate directories do not exist")
#elif defined(__LINUX__) || defined(__APPLE__)
    int returnVal = mkdir(path, S_IRUSR | S_IWUSR | S_IXUSR);
    if (returnVal == -1)
        throw IOException("Can not create path");
#endif
}*/


void Directory::Delete(std::string& path)
{
    Delete(path.c_str());
}

void Directory::Delete(const char* path)
{
    if (strlen(path) == 0)
        throw ArgumentException("Path length can not be 0");
    if (path == nullptr)
        throw ArgumentNullException("Path can not be NULL");
#if defined(__WINDOWS__)
    bool returnVal = RemoveDirectory(path);
    if (!returnVal)
#elif defined(__LINUX__) || defined(__APPLE__)
    int returnVal = rmdir(path);
    if (returnVal == -1)
#endif
        throw IOException("Can not delete path");
}