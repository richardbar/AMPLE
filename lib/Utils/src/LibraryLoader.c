#if defined(_MSC_VER)
    #define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>

#include "LibraryLoader.h"
#include "AMPLE.h"

#if defined(__WINDOWS__)
    #include <Shlobj.h>
#elif defined(__LINUX__) || defined(__APPLE__)
    #include <dlfcn.h>
    #include <pwd.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

typedef struct
{
    const char* LibraryName;
    const char* LibraryLocation;
    void* LibPtr;
} LibStruct;

static const char* GetHomeDir()
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

const char* HomeDir = NULL;

Library* LoadLib(const char* LibraryName) {
    if (!HomeDir)
        HomeDir = GetHomeDir();

    uint32_t LibPosSize = strlen(HomeDir) + 2 * strlen(LibraryName) + 10;
#if defined(__WINDOWS__)
    LibPosSize += strlen("\\.ample\\libs\\");
#elif defined(__LINUX__) || defined(__APPLE__)
    LibPosSize += strlen("/.ample/libs/");
#endif

    LibStruct* lib = (LibStruct*)malloc(sizeof(LibStruct));
    lib->LibraryName = (char*)malloc((strlen(LibraryName) + 1) * sizeof(char));
    if (!lib->LibraryName)
    {
        free(lib);
        return NULL;
    }
    strcpy((char*)lib->LibraryName, LibraryName);
    lib->LibraryLocation = (char*)malloc(LibPosSize * sizeof(char));
    if (!lib->LibraryLocation)
    {
        free((char*)lib->LibraryName);
        free(lib);
        return NULL;
    }
    {
        strcpy((char*)lib->LibraryLocation, HomeDir);
        strcpy((char*)lib->LibraryLocation + strlen(lib->LibraryLocation),
               #if defined(__WINDOWS__)
               "\\.ample\\libs\\"
                #elif defined(__LINUX__) || defined(__APPLE__)
                "/.ample/libs/"
                #endif
        );
        strcpy((char*)lib->LibraryLocation + strlen(lib->LibraryLocation), LibraryName);
        strcpy((char*)lib->LibraryLocation + strlen(lib->LibraryLocation),
                #if defined(__WINDOWS__)
               "\\"
                #elif defined(__LINUX__) || defined(__APPLE__)
                "/"
                #endif
        );
        strcpy((char*)lib->LibraryLocation + strlen(lib->LibraryLocation), LibraryName);
        strcpy((char*)lib->LibraryLocation + strlen(lib->LibraryLocation),
                #if defined(__WINDOWS__)
               ".dll"
                #elif defined(__LINUX__)
                ".so"
                #elif defined(__APPLE__)
                ".dylib"
                #endif
        );
    }

#if defined(__WINDOWS__)
    lib->LibPtr = (void*)LoadLibraryA(TEXT(lib->LibraryLocation));
#elif defined(__LINUX__) || defined(__APPLE__)
    lib->LibPtr = (void*)dlopen(lib->LibraryLocation, RTLD_LAZY);
#endif

    if (!lib->LibPtr)
    {
        free((char*)lib->LibraryLocation);
        free((char*)lib->LibraryName);
        free(lib);
        return NULL;
    }
    return (Library*)lib;
}

void* GetFuncFromLib(Library* Lib, const char* FunctionName)
{
    if (!Lib || !((LibStruct*)Lib)->LibPtr)
        return NULL;

    void* FunctionPointer;

#if defined(__WINDOWS__)
    FunctionPointer = (void*)GetProcAddress((HINSTANCE)((LibStruct*)Lib)->LibPtr, TEXT(FunctionName));
#elif defined(__LINUX__) || defined(__APPLE__)
    FunctionPointer = (void*)dlsym(((LibStruct*)Lib)->LibPtr, FunctionName);
#endif

    return FunctionPointer;
}

void UnloadLib(Library* Lib)
{
    if (!Lib)
        return;

    free((char*)((LibStruct*)Lib)->LibraryLocation);
    free((char*)((LibStruct*)Lib)->LibraryName);
#if defined(__WINDOWS__)
    FreeLibrary((HINSTANCE)((LibStruct*)Lib)->LibPtr);
#elif defined(__LINUX__) || defined(__APPLE__)
    dlclose(((LibStruct*)Lib)->LibPtr);
#endif
}
