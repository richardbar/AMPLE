#ifndef __AMPLE_OUTOFMEMORYEXCEPTION_H__
#define __AMPLE_OUTOFMEMORYEXCEPTION_H__

#include "AMPLE.h"

#include <exception>
#include <string>

class OutOfMemoryException : public std::exception {
public:
    EXPORT explicit OutOfMemoryException(const char *message);

    EXPORT explicit OutOfMemoryException(const std::string &message);

    EXPORT virtual ~OutOfMemoryException() throw();

    EXPORT virtual const char *what() const throw();

private:
    std::string _message;
};

#endif//__AMPLE_OUTOFMEMORYEXCEPTION_H__
