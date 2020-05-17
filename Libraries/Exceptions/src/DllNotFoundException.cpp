#include "../include/DllNotFoundException.h"

DllNotFoundException::DllNotFoundException(const char* message)
{
    _message = std::string(message);
}

DllNotFoundException::DllNotFoundException(const std::string& message)
{
    _message = message;
}

DllNotFoundException::~DllNotFoundException() throw() {}

const char* DllNotFoundException::what() const throw()
{
    return _message.c_str();
}