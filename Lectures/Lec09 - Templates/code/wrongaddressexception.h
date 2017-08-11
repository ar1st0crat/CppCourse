#pragma once

#include <stdexcept>

class WrongAddressException : public std::invalid_argument
{
public:
    WrongAddressException(const char* message, const char* trace="");

    const char* trace() const;

protected:
    const char* trace_;
};
