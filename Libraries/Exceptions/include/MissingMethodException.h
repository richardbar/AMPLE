#ifndef __AMPLE_MISSINGMETHODEXCEPTION_H__
#define __AMPLE_MISSINGMETHODEXCEPTION_H__

#include "AMPLE.h"

#include <exception>
#include <string>

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
