#ifndef __AMPLE_DLL_NOT_FOUND_EXCEPTION_H__
#define __AMPLE_DLL_NOT_FOUND_EXCEPTION_H__

#include "AMPLE.h"

#include <exception>
#include <string>

class DllNotFoundException : public std::exception {
public:
    EXPORT explicit DllNotFoundException(const char* message);
    EXPORT explicit DllNotFoundException(const std::string& message);
    EXPORT virtual ~DllNotFoundException() throw();
    EXPORT virtual const char* what() const throw();
private:
    std::string _message;
};

#endif//__AMPLE_DLL_NOT_FOUND_EXCEPTION_H__