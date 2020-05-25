#ifndef __AMPLE_LIBRARY_AMPLE_H__
#define __AMPLE_LIBRARY_AMPLE_H__


#if defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(WIN32) || defined(_WIN64)
    #if !defined(_MSC_VER)
        #pragma warning You must compile with MSVC in Windows
    #endif
    #define __WINDOWS__
#elif defined(__linux__)
    #if !defined(__GNUC__)
        #pragma warning AMPLE has not been tested with your compiler. If any problem arise please contact me for support.
    #endif
    #define __LINUX__
#elif defined(__APPLE__)
    #pragma warning AMPLE has not been tested in Mac OS.
    #if !defined(__GNUC__)
        #pragma warning AMPLE has not been tested with your compiler. If any problem arise please contact me for support.
    #endif
#else
    #pragma warning AMPLE has not been tested with your Operating system. If any problem arise please look into it and make a pull request with your corrections.
#endif


#if (defined(__amd64) || defined(__amd64__) || defined(__x86_64) || defined(__x86_64__) || defined(_M_AMD64) || defined(_M_X64))
    #define __x86_64__
#elif (defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86))
    #define __x86__
#else
    #pragma warning AMPLE has not been tested for Architectures other than x86 and x86_64. If any problem arise please contact me for support.
#endif


#endif//__AMPLE_LIBRARY_AMPLE_H__
