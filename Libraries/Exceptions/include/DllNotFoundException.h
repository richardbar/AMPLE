#ifndef __AMPLE_DLLNOTFOUNDEXCEPTION_H__
#define __AMPLE_DLLNOTFOUNDEXCEPTION_H__

#include <exception>
#include <string>

#if defined(_MSC_VER)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

class DllNotFoundException : public std::exception {
public:
    EXPORT explicit DllNotFoundException(const char *message);

    EXPORT explicit DllNotFoundException(const std::string &message);

    EXPORT virtual ~DllNotFoundException() throw();

    EXPORT virtual const char *what() const throw();

private:
    std::string _message;
};

#endif//__AMPLE_DLLNOTFOUNDEXCEPTION_H__