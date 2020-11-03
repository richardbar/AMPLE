#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "AMPLE.h"
#include "argProcessor.h"

#include "stdAMPLE.h"

#include "File.h"

#define PRINT_HELP()                                            \
    fprintf(stdout,                                             \
            "AMPLE Runtime\nVersion: %s\nC Version Used: C%s",  \
            __AMPLE_VERSION__,                                  \
            __AMPLE_C_VERSION__);

#define PRINT_VERSION()                                         \
    fprintf(stdout,                                             \
        "AMPLE Runtime\nVersion: %s",                           \
        __AMPLE_VERSION__);

bool HandleArgs(int argNum, char** argPtr, CList filesToRun, CList flags, int* _exitCode)
{
    if (argNum == 0)
    {
        fprintf(stderr, "No arguments passed to AMPLE");
        *_exitCode = 1;
        return false;
    }
    for (int i = 0; i < argNum; i++)
    {
        uint32_t sizeOfArgument = strlen(argPtr[i]);
        if (sizeOfArgument < 2)
            continue;

        if (argPtr[i][0] == '-')    // Setting
        {
            if (argPtr[i][1] == '-' && sizeOfArgument > 3)
            {
                if (strcmp("--help", argPtr[i]) == 0 && argNum != 1)
                {
                    fprintf(stderr, "--help needs to be the only argument");
                    *_exitCode =
                    #if (defined(__WINDOWS__))
                        10022
                    #elif (defined(__LINUX__) || defined(__APPLE__))
                        126
                    #else
                        1
                    #endif
                        ;
                    return false;
                }
                else if (strcmp("--help", argPtr[i]) == 0)
                {
                    PRINT_HELP();
                    *_exitCode = 0;
                    return false;
                }
                else if (strcmp("--version", argPtr[i]) == 0 && argNum != 1)
                {
                    fprintf(stderr, "--help needs to be the only argument");
                    *_exitCode =
                    #if (defined(__WINDOWS__))
                            10022
                    #elif (defined(__LINUX__) || defined(__APPLE__))
                        126
                    #else
                        1
                    #endif
                            ;
                    return false;
                }
                else if (strcmp("--version", argPtr[i]) == 0)
                {
                    PRINT_VERSION();
                    *_exitCode = 0;
                    return false;
                }
                else if (strcmp("--printRegisters", argPtr[i]) == 0)
                {
                    if (!InsertElementToList(flags, "printRegisters"))
                        return false;
                }
                else if (strcmp("--notClearMemoryAndRegisters", argPtr[i]) == 0)
                {
                    if (!InsertElementToList(flags, "notClearMemoryAndRegisters"))
                        return false;
                }
                else
                {
                    fprintf(stderr, "\"%s\" argument is not recognized\n", argPtr[i]);
                    *_exitCode =
                    #if (defined(__WINDOWS__))
                        10022
                    #elif (defined(__LINUX__) || defined(__APPLE__))
                        126
                    #else
                        1
                    #endif
                        ;
                    return false;
                }
            }
            else if (sizeOfArgument == 2)
            {
                if (argPtr[i][1] == 'h' && argNum != 1)
                {
                    fprintf(stderr, "-h needs to be the only argument");
                    *_exitCode =
                    #if (defined(__WINDOWS__))
                        10022
                    #elif (defined(__LINUX__) || defined(__APPLE__))
                        126
                    #else
                        1
                    #endif
                        ;
                    return false;
                }
                else if (argPtr[i][1] == 'h')
                {
                    PRINT_HELP();
                    *_exitCode = 0;
                    return false;
                }
                else if (argPtr[i][1] == 'v' && argNum != 1)
                {
                    fprintf(stderr, "-v needs to be the only argument");
                    *_exitCode =
                    #if (defined(__WINDOWS__))
                            10022
                    #elif (defined(__LINUX__) || defined(__APPLE__))
                        126
                    #else
                        1
                    #endif
                            ;
                    return false;
                }
                else if (argPtr[i][1] == 'v')
                {
                    PRINT_VERSION();
                    *_exitCode = 0;
                    return false;
                }
                else if (argPtr[i][1] == 'p')
                {
                    if (!InsertElementToList(flags, "printRegisters"))
                        return false;
                }
                else if (argPtr[i][1] == 'c')
                {
                    if (!InsertElementToList(flags, "notClearMemoryAndRegisters"))
                        return false;
                }
                else
                {
                    fprintf(stderr, "\"%s\" argument is not recognized\n", argPtr[i]);
                    *_exitCode =
                    #if (defined(__WINDOWS__))
                        10022
                    #elif (defined(__LINUX__) || defined(__APPLE__))
                        126
                    #else
                        1
                    #endif
                        ;
                    return false;
                }
            }
            else
            {
                fprintf(stderr, "Argument is not recognizable");
                *_exitCode =
                #if (defined(__WINDOWS__))
                    10022
                #elif (defined(__LINUX__) || defined(__APPLE__))
                    126
                #else
                    1
                #endif
                    ;
                return false;
            }
        }
        else if (FileExists(argPtr[i]))
        {
            InsertElementToList(filesToRun, argPtr[i]);
        }
        else
        {
            fprintf(stderr, "Argument is not recognizable");
            *_exitCode =
            #if (defined(__WINDOWS__))
                10022
            #elif (defined(__LINUX__) || defined(__APPLE__))
                126
            #else
                1
            #endif
                ;
            return false;
        }
    }

    return true;
}