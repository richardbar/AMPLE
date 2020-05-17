#ifndef __AMPLE_LIBRARIES_LIBRARY_H__
#define __AMPLE_LIBRARIES_LIBRARY_H__

#include <string>
#include <vector>

#if defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(WIN32) || defined(_WIN64)
    #include <Windows.h>
#endif

class Library
{
public:
    static bool InstallLibraries(std::vector<std::string>& libraries);
    static bool InstallLibrary(std::string& library);

    explicit Library(std::string& Library);
    void* GetFunction(std::string& Function);
    ~Library();
private:
    std::string LibraryName;
    static bool LibraryIsInstalled(std::string& library);
    void LoadLib(std::string& Library);

#if defined(_WIN32) || defined(WIN32)
    HINSTANCE LibraryInstance;
#elif defined(__linux__)
    void* LibraryInstance;
#endif
};

#endif//__AMPLE_LIBRARIES_LIBRARY_H__
