#pragma once

#include <vector>
#include "Card.h"

/** @interface IScoreCounter
* <p>An interface for classes whose purpose is providing the technique for calculating the total score in the set of cards</p>
*
* @author ar1st0crat
*/
class IScoreCounter
{
public:
    /** Virtual destructor */
    virtual ~IScoreCounter() {}
    /** Method calculates the total score in a custom set of cards (particularly, in a cardholder's hand) */
    virtual int countScore(const std::vector<Card>& hand) const = 0;
};
