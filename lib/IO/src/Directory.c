#include <stdlib.h>
#include <stdio.h>

#include "AMPLE.h"

#if defined(__LINUX__) || defined(__APPLE__)
    #include <pwd.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

#include "Directory.h"

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