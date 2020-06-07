#ifndef __AMPLE_ARGUMENT_EXCEPTION_H__
#define __AMPLE_ARGUMENT_EXCEPTION_H__

#include "AMPLE.h"

#include <exception>
#include <string>

class ArgumentException : public std::exception {
public:
    EXPORT explicit ArgumentException(const char* message);
    EXPORT explicit ArgumentException(const std::string& message);
    EXPORT virtual ~ArgumentException() throw();
    EXPORT virtual const char* what() const throw();
private:
    std::string _message;
};

#endif//__AMPLE_ARGUMENT_EXCEPTION_H__