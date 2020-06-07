#ifndef __AMPLE_CORRUPTED_PROGRAM_EXCEPTION_H__
#define __AMPLE_CORRUPTED_PROGRAM_EXCEPTION_H__

#include "AMPLE.h"

#include <exception>
#include <string>

class CorruptedProgramException : public std::exception {
public:
    EXPORT explicit CorruptedProgramException(const char* message);
    EXPORT explicit CorruptedProgramException(const std::string& message);
    EXPORT virtual ~CorruptedProgramException() throw();
    EXPORT virtual const char* what() const throw();
private:
    std::string _message;
};

#endif//__AMPLE_CORRUPTED_PROGRAM_EXCEPTION_H__