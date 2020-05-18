#include "MissingMethodException.h"

MissingMethodException::MissingMethodException(const char *message)
{
    _message = std::string(message);
}

MissingMethodException::MissingMethodException(const std::string &message)
{
    _message = message;
}

MissingMethodException::~MissingMethodException() throw() {}

const char* MissingMethodException::what() const throw()
{
    return _message.c_str();
}