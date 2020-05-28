#include "CorruptedProgramException.h"

CorruptedProgramException::CorruptedProgramException(const char* message)
{
    _message = std::string(message);
}

CorruptedProgramException::CorruptedProgramException(const std::string& message)
{
    _message = message;
}

CorruptedProgramException::~CorruptedProgramException() throw() {}

const char* CorruptedProgramException::what() const throw()
{
    return _message.c_str();
}