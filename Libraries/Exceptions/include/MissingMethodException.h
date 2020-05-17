#ifndef __AMPLE_MISSINGMETHODEXCEPTION_H__
#define __AMPLE_MISSINGMETHODEXCEPTION_H__

#include <exception>
#include <string>

class MissingMethodException : public std::exception
{
public:
    explicit MissingMethodException(const char* message);
    explicit MissingMethodException(const std::string& message);
    virtual ~MissingMethodException() throw();
    virtual const char* what() const throw();

private:
    std::string _message;
};

#endif//__AMPLE_MISSINGMETHODEXCEPTION_H__
