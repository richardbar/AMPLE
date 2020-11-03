#pragma once

#if  (  defined(_WIN32)    || \
        defined(__WIN32__) || \
        defined(__NT__)    || \
        defined(WIN32)     || \
        defined(_WIN64)   )
    #define __WINDOWS__
    #if (!defined(_MSC_VER))
        #warning AMPLE is tested in the MS Compiler If any problem arises \
                 you will have to fix them by yourself
    #endif
#elif ( defined(__linux__))
    #define __LINUX__
    #if (!defined(__GNUC__))
        #warning AMPLE is tested in the GNU C Compiler. If any problem arises \
                 you will have to fix them by yourself
    #endif
#elif ( defined(__AMPLE__))
    #if (!defined(__GNUC__))
        #warning AMPLE is tested in the GNU C Compiler. If any problem arises \
                 you will have to fix them by yourself
    #endif
#elif (!defined(__APPLE__))
    #warning AMPLE does not support your platform. If any problem arises \
             you will have to fix them by yourself
#endif


#if   (defined(__amd64)    || \
       defined(__amd64__)  || \
       defined(__x86_64)   || \
       defined(__x86_64__) || \
       defined(_M_AMD64)   || \
       defined(_M_X64))
    #if (!defined(__x86_64__))
        #define __x86_64__
    #endif
#elif ( defined(i386)     || \
        defined(__i386)   || \
        defined(__i386__) || \
        defined(_M_IX86))
    #if (!defined(__x86__))
        #define __x86__
    #endif
#elif ((defined(_M_ARM) && defined(_M_ARM64)) && \
       !defined(__aarch64) && \
       defined(__arm__))
    #if (!defined(__ARM32__))
        #define __ARM32__
    #endif
#elif ( defined(_M_ARM) || \
        defined(__aarch64__))
    #if (!defined(__ARM64__))
        #define __ARM64__
    #endif
#else
    #warning AMPLE does not support your architecture. If any problem arises \
             you will have to fix them by yourself
#endif


#if   ( defined(__WINDOWS__)                      && defined(_MSC_VER))
    #define EXPORT __declspec(dllexport)
	#define IMPORT __declspec(dllimport)
#elif ((defined(__LINUX__) || defined(__APPLE__)) && defined(__GNUC__))
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#endif


#if (!defined(__WINDOWS__))
    #define TEXT(...) __VA_ARGS__
#endif