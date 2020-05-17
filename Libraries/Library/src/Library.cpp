#include "Library.h"
#include "DllNotFoundException.h"
#include "MissingMethodException.h"

#if defined(__linux__)
    #include <dlfcn.h>
#endif

bool Library::InstallLibraries(std::vector<std::string>& libraries)
{
    for (auto& library : libraries)
        if (!InstallLibrary(library))
        {
            fprintf(stderr, "Library: \"%s\" did not install properly.\n", library.c_str());
            return false;
        }

    return true;
}

bool Library::InstallLibrary(std::string& library)
{
    if (LibraryIsInstalled(library)) return true;
    return true;
}

Library::Library(std::string& Library)
{
    LoadLib(Library);
}

void* Library::GetFunction(std::string& Function)
{
    void* FPointer;
    if (LibraryInstance)
#if defined(_WIN32) || defined(WIN32)
        FPointer = (void*)GetProcAddress(LibraryInstance, Function.c_str());
#elif defined(__linux__)
        FPointer = dlsym(LibraryInstance, Function.c_str());
#endif
    else
        throw DllNotFoundException(std::string("Dynamic library \"").append(this->LibraryName).append("\" does not exist"));
    if (!FPointer)
        throw MissingMethodException(std::string("Dynamic Function \"").append(Function).append("\" could not be successfully binded from \"").append(this->LibraryName).append("\" Library"));
    return FPointer;
}

Library::~Library()
{
    if (LibraryInstance)
#if defined(_WIN32) || defined(WIN32)
        FreeLibrary(LibraryInstance);
#elif defined(__linux__)
        dlclose(LibraryInstance);
#endif
}

bool Library::LibraryIsInstalled(std::string& library)
{
    return false;
}

void Library::LoadLib(std::string& Library)
{
#if defined(_WIN32) || defined(WIN32)
    LibraryInstance = LoadLibrary(TEXT(Library.c_str()));
#elif defined(__linux__)
    LibraryInstance = (void*)dlopen(Library.c_str(), RTLD_LAZY);
#endif
    if (!LibraryInstance)
        throw DllNotFoundException(std::string("Dynamic library \"").append(Library).append("\" does not exist"));
    this->LibraryName = Library;
}