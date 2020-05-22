#ifndef AMPLE_INDEXOUTOFRANGEEXCEPTION_H
#define AMPLE_INDEXOUTOFRANGEEXCEPTION_H

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

class IndexOutOfRangeException : public std::exception {
public:
    EXPORT explicit IndexOutOfRangeException(const char *message);

    EXPORT explicit IndexOutOfRangeException(const std::string &message);

    EXPORT virtual ~IndexOutOfRangeException() throw();

    EXPORT virtual const char *what() const throw();

private:
    std::string _message;
};

#endif //AMPLE_INDEXOUTOFRANGEEXCEPTION_H