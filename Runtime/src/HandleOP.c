#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AMPLE.h"
#include "HandleOP.h"

#include "Instruction.h"

#if defined(__WINDOWS__)
    #include <Shlobj.h>
#elif defined(__LINUX__) || defined(__APPLE__)
    #include <dlfcn.h>
    #include <pwd.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

#define MAX_VERSIONS 512

bool (*OPCODE_HANDLER)(Instruction, uint32_t*, CList, CList) = NULL;

void** VersionFilePointers = NULL;
bool (**Versions)(Instruction, uint32_t*, CList, CList) = NULL;

bool HANDLE_OPCODE(Instruction instruction, uint32_t* position, CList Memory, CList Registers)
{
    return (OPCODE_HANDLER) ? OPCODE_HANDLER(instruction, position, Memory, Registers) : false;
}

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

static bool LoadVersion(uint32_t VERSION)
{
    char* file = (char*)malloc(1024 * sizeof(char));
    memset(file, 0, 1024 * sizeof(char));

    snprintf(file, 1024, "%s/.ample/versions/OPCODE-V%d", GetHomeDir(), VERSION);

    char* function = (char*)malloc(1024 * sizeof(char));
    memset(function, 0, 1024 * sizeof(char));

    snprintf(function, 1024, "HANDLE_OPCODE_V%d", VERSION);

#if defined(__WINDOWS__)
    VersionFilePointers[VERSION] = (void*)LoadLibraryA(TEXT(lib->LibraryLocation));
#elif defined(__LINUX__) || defined(__APPLE__)
    VersionFilePointers[VERSION] = (void*)dlopen(file, RTLD_LAZY);
#endif

    if (VersionFilePointers[VERSION] == NULL)
    {
        free(file);
        free(function);
        return false;
    }

#if defined(__WINDOWS__)
    Versions[VERSION] = (void*)GetProcAddress((HINSTANCE)VersionFilePointers[VERSION], TEXT(function));
#elif defined(__LINUX__) || defined(__APPLE__)
    Versions[VERSION] = (void*)dlsym(VersionFilePointers[VERSION], function);
#endif

    if (Versions[VERSION] == NULL)
    {
        free(file);
        free(function);
        return false;
    }

    free(file);
    free(function);
    return true;
}

bool SET_OPCODE_VERSION(uint32_t INSTRUCTION_VERSION)
{
    if (Versions == NULL)
    {
        Versions = (bool(**)(Instruction, uint32_t*, CList, CList))malloc(MAX_VERSIONS * sizeof(bool(*)(Instruction, uint32_t*, CList, CList)));
        memset(Versions, 0, MAX_VERSIONS * sizeof(bool(*)(Instruction, uint32_t*, CList, CList)));

        VersionFilePointers = (void**)malloc(MAX_VERSIONS * sizeof(void*));
        memset(VersionFilePointers, 0, MAX_VERSIONS * sizeof(void*));
    }

    if (INSTRUCTION_VERSION >= MAX_VERSIONS)
        return false;

    if (Versions[INSTRUCTION_VERSION] == NULL)
    {
        if (!LoadVersion(INSTRUCTION_VERSION))
            return false;
    }

    OPCODE_HANDLER = Versions[INSTRUCTION_VERSION];

    return true;
}