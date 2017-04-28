#pragma once

#include "IScoreCounter.h"


/** @class BlackjackScoreCounter
* <p>Implements the IScoreCounter interface for calculating the total score of a cardholder's hand
*
* @author ar1st0crat
*/
class BlackjackScoreCounter : public IScoreCounter
{
public:
    int countScore(const std::vector<Card>& hand) const override;
};
