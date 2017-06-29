#pragma once

#include <vector>
#include "../../Model/IGame.h"

/**
 * @interface IDealStrategy
 * @brief Interface declares methods for organizing deals
 *
 * @author ar1st0crat
 */
class IDealStrategy
{
public:
    /** Virtual destructor */
    virtual ~IDealStrategy() {}

    /** Method should contain logic of initial deal */
    virtual void initialDeal(IGame& game) const = 0;

    /** Method should define how to provide cards to player */
    virtual void giveCardToPlayer(IGame& game) const = 0;

    /** Method should define how to provide cards to dealer */
    virtual void giveCardToDealer(IGame& game) const = 0;
};
