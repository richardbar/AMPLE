#include "AMPLE.h"

#include "Library.h"
#include "DllNotFoundException.h"
#include "MissingMethodException.h"

#if defined(__WINDOWS__)
    #include <Shlobj.h>
    #include <Windows.h>
#elif defined(__LINUX__) || defined(__APPLE__)
    #include <dlfcn.h>
    #include <pwd.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

const char* GetHomeDir()
{
#if defined(__WINDOWS__)
    char* returny;
    size_t reqSize;
    getenv_s(&reqSize, NULL, 0, "USERPROFILE");
    returny = (char*)malloc(reqSize * sizeof(char));
    getenv_s(&reqSize, returny, reqSize, "USERPROFILE");
    return returny;
#elif defined(__LINUX__) || defined(__APPLE__)
    struct passwd* pw = getpwuid(getuid());
    return pw->pw_dir;
#endif
}


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
#if defined(__WINDOWS__)
    LoadLib(std::string(GetHomeDir()).append(R"(\.ample\libs\)").append(Library).append(".dll"));
#elif defined(__LINUX__) || defined(__APPLE__)
    LoadLib(std::string(GetHomeDir()).append("/.ample/libs/").append(Library).append(".so"));
#endif
}

void* Library::GetFunction(std::string& Function)
{
    void* FPointer;
    if (LibraryInstance)
#if defined(__WINDOWS__)
        FPointer = (void*)GetProcAddress((HINSTANCE)LibraryInstance, Function.c_str());
#elif defined(__LINUX__) || defined(__APPLE__)
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
#if defined(__WINDOWS__)
        FreeLibrary((HINSTANCE)LibraryInstance);
#elif defined(__LINUX__) || defined(__APPLE__)
        dlclose(LibraryInstance);
#endif
}

bool Library::LibraryIsInstalled(std::string& library)
{
    FILE* fptr;
#if defined(__WINDOWS__)
    std::string libPath = std::string(GetHomeDir()).append(R"(\.ample\libs\)").append(library).append(".dll");
    fopen_s(&fptr, libPath.c_str(), "r");
#elif defined(__LINUX__) || defined(__APPLE__)
    std::string libPath = std::string(GetHomeDir()).append("/.ample/libs/").append(library).append(".so");
    fptr = fopen(libPath.c_str(), "r");
#endif
    if (fptr)
    {
        fclose(fptr);
        return true;
    }
    return false;
}

void Library::LoadLib(std::string& Library)
{
#if defined(__WINDOWS__)
    LibraryInstance = LoadLibrary(TEXT(Library.c_str()));
#elif defined(__LINUX__) || defined(__APPLE__)
    LibraryInstance = (void*)dlopen(Library.c_str(), RTLD_LAZY);
#endif
    if (!LibraryInstance)
        throw DllNotFoundException(std::string("Dynamic library \"").append(Library).append("\" does not exist"));
    this->LibraryName = Library;
}