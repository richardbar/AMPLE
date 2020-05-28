#ifndef __AMPLE_LIBRARY_AMPLE_ARCHITECTURE_DETECTION_H__
#define __AMPLE_LIBRARY_AMPLE_ARCHITECTURE_DETECTION_H__

#if (defined(__amd64) || defined(__amd64__) || defined(__x86_64) || defined(__x86_64__) || defined(_M_AMD64) || defined(_M_X64))
    #ifndef __x86_64__
        #define __x86_64__
    #endif
#elif (defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86))
    #ifndef __x86__
        #define __x86__
    #endif
#else
    #pragma warning AMPLE has not been tested for Architectures other than x86 and x86_64. If any problem arise please contact me for support.
#endif

#endif//__AMPLE_LIBRARY_AMPLE_ARCHITECTURE_DETECTION_H__