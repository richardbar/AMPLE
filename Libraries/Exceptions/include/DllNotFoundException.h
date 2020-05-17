#ifndef __AMPLE_DLLNOTFOUNDEXCEPTION_H__
#define __AMPLE_DLLNOTFOUNDEXCEPTION_H__

#include <exception>
#include <string>

class DllNotFoundException : public std::exception
{
public:
    explicit DllNotFoundException(const char* message);
    explicit DllNotFoundException(const std::string& message);
    virtual ~DllNotFoundException() throw();
    virtual const char* what() const throw();

private:
    std::string _message;
};
#endif//__AMPLE_DLLNOTFOUNDEXCEPTION_H__