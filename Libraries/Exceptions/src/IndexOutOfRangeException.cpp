#include "IndexOutOfRangeException.h"

IndexOutOfRangeException::IndexOutOfRangeException(const char* message)
{
    _message = std::string(message);
}

IndexOutOfRangeException::IndexOutOfRangeException(const std::string& message)
{
    _message = message;
}

IndexOutOfRangeException::~IndexOutOfRangeException() throw() {}

const char* IndexOutOfRangeException::what() const throw()
{
    return _message.c_str();
}