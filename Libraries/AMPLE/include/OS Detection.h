#ifndef __AMPLE_LIBRARY_AMPLE_OS_DETECTION_H__
#define __AMPLE_LIBRARY_AMPLE_OS_DETECTION_H__

#if defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(WIN32) || defined(_WIN64)
    #if !defined(_MSC_VER)
        //#pragma warning You must compile with MSVC in Windows
    #endif
    #define __WINDOWS__
#elif defined(__linux__)
    #if !defined(__GNUC__)
        //#pragma warning AMPLE has not been tested with your compiler. If any problem arise please contact me for support.
    #endif
    #define __LINUX__
#elif defined(__APPLE__)
    //#pragma warning AMPLE has not been tested in Mac OS.
    #if !defined(__GNUC__)
        //#pragma warning AMPLE has not been tested with your compiler. If any problem arise please contact me for support.
    #endif
#else
    //#pragma warning AMPLE has not been tested with your Operating system. If any problem arise please look into it and make a pull request with your corrections.
#endif

#endif//__AMPLE_LIBRARY_AMPLE_OS_DETECTION_H__