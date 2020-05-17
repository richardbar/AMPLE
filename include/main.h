#ifndef __AMPLE_MAIN_H__
#define __AMPLE_MAIN_H__

#if defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(WIN32) || defined(_WIN64)
    #if !defined(_MSC_VER)
        #error You must compile with MSVC in Windows
    #endif
#elif defined(__linux__)
    #if !defined(__GNUC__)
        #error You must compile with GNU C Compiler in Linux
    #endif
#elif defined(__APPLE__)
    #if !defined(__GNUC__)
        #error You must compile with GNU C Compiler in Apple Mac OS
    #else
        #pragma warning AMPLE has not been tested in Mac OS. In addition dynamic libraries do not load
    #endif
#else
    #error AMPLE does not support your platform yet
#endif


#if !(defined(__amd64) || defined(__amd64__) || defined(__x86_64) || defined(__x86_64__) || defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_AMD64) || defined(_M_X64) || defined(_M_IX86))
    #pragma warning AMPLE has not been tested for Architectures other than x86 and x86_64
#endif

#include <list>
#include <string>

#define HANDLED_MAIN(CLASS)\
int main(int argc, char** argv)\
{\
    auto args = std::vector<std::string>();\
    for (int i = 1; i < argc; i++)\
    args.emplace_back(std::string(argv[i]));\
    CLASS::Main(args);\
}

#endif//__AMPLE_MAIN_H__
