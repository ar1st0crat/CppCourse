#include "BlackjackException.h"


/** Parameterized constructor
* <p>Initializes BlackjackException with the name of a cardholder who's got some blackjack game exception (score=21 by default)</p>
* @param [in] const std::string& player the name of a cardholder who's been busted */
BlackjackException::BlackjackException(const std::string& player) noexcept 
    : player_(player), message_("Blackjack!")
{
}

/** Virtual destructor */
BlackjackException::~BlackjackException() noexcept
{
}

/** Method overrides the what() method of standard exception class
* @returns const char* The message of an exception ("Blackjack" by default)  */
const char* BlackjackException::what() const noexcept
{
    return message_;
}

/** Getter for the player's name
* @returns The player's name who's got the exception */
std::string BlackjackException::getPlayerName() noexcept
{
    return player_;
}
