#ifndef AMPLE_INDEXOUTOFRANGEEXCEPTION_H
#define AMPLE_INDEXOUTOFRANGEEXCEPTION_H

#include <exception>
#include <string>

class IndexOutOfRangeException : public std::exception
{
public:
    explicit IndexOutOfRangeException(const char* message);
    explicit IndexOutOfRangeException(const std::string& message);
    virtual ~IndexOutOfRangeException() throw();
    virtual const char* what() const throw();

private:
    std::string _message;
};

#endif //AMPLE_INDEXOUTOFRANGEEXCEPTION_H