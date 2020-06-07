#ifndef __AMPLE_FILE_NOT_FOUND_H__
#define __AMPLE_FILE_NOT_FOUND_H__

#include "AMPLE.h"

#include <exception>
#include <string>

class FileNotFoundException : public std::exception {
public:
    EXPORT explicit FileNotFoundException(const char* message);
    EXPORT explicit FileNotFoundException(const std::string& message);
    EXPORT virtual ~FileNotFoundException() throw();
    EXPORT virtual const char* what() const throw();
private:
    std::string _message;
};

#endif//__AMPLE_FILE_NOT_FOUND_H__
