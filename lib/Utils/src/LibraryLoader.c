#if defined(_MSC_VER)
    #define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static void* OpenLibrary(const char* Location)
{
    void* returnVal = NULL;

#if defined(__WINDOWS__)
    returnVal = (void*)LoadLibraryA(TEXT(Location));
#elif defined(__LINUX__) || defined(__APPLE__)
    returnVal = (void*)dlopen(Location, RTLD_LAZY);
#endif

    return returnVal;
}

const char* HomeDir = NULL;

Library* LoadOPCodeVersion(uint32_t Version)
{
    if (!HomeDir)
        HomeDir = GetHomeDir();

    uint32_t LibPosSize = strlen(HomeDir) + 15;
#if defined(__WINDOWS__)
    LibPosSize += strlen("\\.ample\\versions\\");
#elif defined(__LINUX__) || defined(__APPLE__)
    LibPosSize += strlen("/.ample/versions/");
#endif

    LibStruct* lib = (LibStruct*)malloc(sizeof(LibStruct));
    lib->LibraryName = (char*)malloc((strlen("OPCODE-V") + 4) * sizeof(char));
    if (!lib->LibraryName)
    {
        free(lib);
        return NULL;
    }

    lib->LibraryLocation = (char*)malloc(LibPosSize * sizeof(char));
    if (!lib->LibraryLocation)
    {
        free((void*)lib->LibraryName);
        free(lib);
        return NULL;
    }

    snprintf((char*)(lib->LibraryName), strlen("OPCODE-V") + 4, "OPCODE-V%d", Version);
    snprintf((char*)(lib->LibraryLocation),
             LibPosSize,
             "%s%s%s%sversions%sOPCODE-V%d.%s",
             HomeDir,
#if defined(__WINDOWS__)
             "\\",
             ".ample",
             "\\",
             "\\",
#elif defined(__LINUX__) || defined(__APPLE__)
             "/",
             ".ample",
             "/",
             "/",
#endif
             Version,
#if defined(__WINDOWS__)
             "dll"
#elif defined(__LINUX__)
             "so"
#elif defined(__APPLE__)
             "dylib"
#endif
             );

    lib->LibPtr = OpenLibrary(lib->LibraryLocation);
    if (!lib->LibPtr)
    {
        free((void*)(lib->LibraryLocation));
        free((void*)(lib->LibraryName));
        free(lib);
        return NULL;
    }

    return (Library*)lib;
}

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

    lib->LibPtr = OpenLibrary(lib->LibraryLocation);

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
