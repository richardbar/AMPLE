#ifndef __AMPLE_MISSINGMETHODEXCEPTION_H__
#define __AMPLE_MISSINGMETHODEXCEPTION_H__

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

class MissingMethodException : public std::exception {
public:
    EXPORT explicit MissingMethodException(const char *message);

    EXPORT explicit MissingMethodException(const std::string &message);

    EXPORT virtual ~MissingMethodException() throw();

    EXPORT virtual const char *what() const throw();

private:
    std::string _message;
};

#endif//__AMPLE_MISSINGMETHODEXCEPTION_H__
