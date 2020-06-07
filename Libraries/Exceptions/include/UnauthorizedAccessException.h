#ifndef __AMPLE_UNAUTHORIZED_ACCESS_EXCEPTION_H__
#define __AMPLE_UNAUTHORIZED_ACCESS_EXCEPTION_H__

#include "AMPLE.h"

#include <exception>
#include <string>

class UnauthorizedAccessException : public std::exception {
public:
    EXPORT explicit UnauthorizedAccessException(const char* message);
    EXPORT explicit UnauthorizedAccessException(const std::string& message);
    EXPORT virtual ~UnauthorizedAccessException() throw();
    EXPORT virtual const char* what() const throw();
private:
    std::string _message;
};

#endif//__AMPLE_UNAUTHORIZED_ACCESS_EXCEPTION_H__
