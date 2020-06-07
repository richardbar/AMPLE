#include "IOException.h"

#define CLASS_NAME IOException

CLASS_NAME::CLASS_NAME(const char* message)
{
    _message = std::string(message);
}

CLASS_NAME::CLASS_NAME(const std::string& message)
{
    _message = message;
}

CLASS_NAME::~CLASS_NAME() throw() {}

const char* CLASS_NAME::what() const throw()
{
    return _message.c_str();
}