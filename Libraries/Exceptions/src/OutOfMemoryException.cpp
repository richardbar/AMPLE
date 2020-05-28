#include "OutOfMemoryException.h"

OutOfMemoryException::OutOfMemoryException(const char *message)
{
    _message = std::string(message);
}

OutOfMemoryException::OutOfMemoryException(const std::string &message)
{
    _message = message;
}

OutOfMemoryException::~OutOfMemoryException() throw() {}

const char* OutOfMemoryException::what() const throw()
{
    return _message.c_str();
}
