#pragma once

#include "BlackjackException.h"


/** @class BustException
* <p>Reflects the situation when some cardholder gets busted</p>
*
* @author ar1st0crat
*/
class BustException : public BlackjackException
{
public:
    BustException(const std::string& player, int score);
    virtual const char* what() const noexcept override;

private:
    /** The score of a cardholder who's been busted */
    int score_;
};
