#pragma once

#include <stdexcept>
#include <string>


/** @class BlackjackException
* <p>Reflects the situation when something extraordinary happens during the game</p>
*
* @author ar1st0crat
*/
class BlackjackException : public std::exception
{
public:
    BlackjackException(const std::string& player) noexcept;
    virtual ~BlackjackException() noexcept;

    virtual const char* what() const noexcept override;
    std::string getPlayerName() noexcept;

protected:
    /** The name of a cardholder */
    std::string player_;
    /** Message of the exception */
    const char* message_;
};
