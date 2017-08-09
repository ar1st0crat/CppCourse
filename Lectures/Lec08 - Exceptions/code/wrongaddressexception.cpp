#include "wrongaddressexception.h"

WrongAddressException::WrongAddressException(const char* message, const char* trace)
    : std::invalid_argument(message), trace_(trace)
{
}

const char* WrongAddressException::trace() const
{
    return trace_;
}
