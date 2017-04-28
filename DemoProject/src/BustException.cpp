#include "BustException.h"

/** Parameterized constructor
* <p>Initializes BustException with the name and the total score of a cardholder who's been busted</p>
* @param [in] const std::string& player The name of a cardholder who's been busted
* @param [in] int score The score of a cardholder who's been busted  */
BustException::BustException(const std::string& player, int score)
    : BlackjackException(player), score_(score)
{
    message_ = "Bust!";
}


/** Method overrides the what() method of standard exception class
* @returns const char*  The message of an exception ("Bust!")  */
const char* BustException::what() const noexcept
{
    return message_;
}
