#if defined(__WITH_INSTALL__)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "AMPLE.h"
#include "Directory.h"
#include "File.h"

#include "install.h"


typedef struct
{
    bool initialized;
    char* fname;
    int64_t fnameLength;
    uint8_t mode;
    FILE* fptr;
} FileStruct;

static size_t writeData(void* ptr, size_t size, size_t nmemb, void* stream)
{
    return fwrite(ptr, size, nmemb, (FILE*)stream);
}

bool Download(uint8_t type, const char* name, const char* url)
{
    const char* HomeDir = GetHomeDir();
    char* fname = (char*)malloc((strlen(HomeDir) + 38) * sizeof(char));
    if (!fname)
    {
#if defined(__WINDOWS__)
        free((void*)HomeDir);
#endif
        return false;
    }
    memset(fname, 0, (strlen(HomeDir) + 38) * sizeof(char));
    snprintf(
            fname,
            strlen(HomeDir) + 38,
            "%s%s.ample%s%s%sOPCODE-V%s.%s",
            HomeDir,
#if defined(__WINDOWS__)
            "\\",
            "\\",
            (type == RUNTIME) ? "versions" : "libs",
            "\\",
            name,
            "dll"
#elif defined(__LINUX__) || defined(__APPLE__)
            "/",
            "/",
            (type == RUNTIME) ? "versions" : "libs",
            "/",
            name,
    #if defined(__LINUX__)
            "so"
    #else
            "dylib"
    #endif
#endif
    );

    CURL* curl_handler;
    NFILE fptr = NFileOpen(fname, FILE_WRITE | FILE_BINARY);
    if (!fptr)
    {
#if defined(__WINDOWS__)
        free((void*)HomeDir);
#endif
        free(fname);
        return false;
    }

    curl_global_init(CURL_GLOBAL_ALL);

    curl_handler = curl_easy_init();

    curl_easy_setopt(curl_handler, CURLOPT_URL, url);
    curl_easy_setopt(curl_handler, CURLOPT_VERBOSE, 0);
    curl_easy_setopt(curl_handler, CURLOPT_VERBOSE, 0);
    curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, ((FileStruct*)writeData)->fptr);
    curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, fptr);
    curl_easy_perform(curl_handler);

    curl_easy_cleanup(curl_handler);

    curl_global_cleanup();

    NFileClose(fptr);
    free((void*)fname);
#if defined(__WINDOWS__)
    free((void*)HomeDir);
#endif

    return true;
}

#endif