#ifndef __AMPLE_IO_EXCEPTION_H__
#define __AMPLE_IO_EXCEPTION_H__

#include "AMPLE.h"

#include <exception>
#include <string>

class IOException : public std::exception {
public:
    EXPORT explicit IOException(const char* message);
    EXPORT explicit IOException(const std::string& message);
    EXPORT virtual ~IOException() throw();
    EXPORT virtual const char* what() const throw();
private:
    std::string _message;
};

#endif//__AMPLE_IO_EXCEPTION_H__
