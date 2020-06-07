#ifndef AMPLE_INDEX_OUT_OF_RANGE_EXCEPTION_H__
#define AMPLE_INDEX_OUT_OF_RANGE_EXCEPTION_H__

#include "AMPLE.h"

#include <exception>
#include <string>

class IndexOutOfRangeException : public std::exception {
public:
    EXPORT explicit IndexOutOfRangeException(const char* message);
    EXPORT explicit IndexOutOfRangeException(const std::string& message);
    EXPORT virtual ~IndexOutOfRangeException() throw();
    EXPORT virtual const char* what() const throw();
private:
    std::string _message;
};

#endif //AMPLE_INDEX_OUT_OF_RANGE_EXCEPTION_H__