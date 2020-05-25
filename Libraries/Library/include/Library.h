#ifndef __AMPLE_LIBRARIES_LIBRARY_H__
#define __AMPLE_LIBRARIES_LIBRARY_H__

#include <string>
#include <vector>

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

    void* LibraryInstance;
};

#endif//__AMPLE_LIBRARIES_LIBRARY_H__
