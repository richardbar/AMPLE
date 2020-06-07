#ifndef __AMPLE_ARGUMENT_NULL_EXCEPTION_H__
#define __AMPLE_ARGUMENT_NULL_EXCEPTION_H__

#include "AMPLE.h"

#include <exception>
#include <string>

class ArgumentNullException : public std::exception {
public:
    EXPORT explicit ArgumentNullException(const char* message);
    EXPORT explicit ArgumentNullException(const std::string& message);
    EXPORT virtual ~ArgumentNullException() throw();
    EXPORT virtual const char* what() const throw();
private:
    std::string _message;
};

#endif//__AMPLE_ARGUMENT_NULL_EXCEPTION_H__