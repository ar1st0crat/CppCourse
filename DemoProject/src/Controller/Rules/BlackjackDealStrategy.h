#pragma once

#include "IDealStrategy.h"

/**
 * @class BlackjackDealStrategy
 * @brief Class contains implementation of ordinary blackjack strategy:
 *    <ul>
 *        <li>dealer's given one card (and no hole card)</li>
 *        <li>player's given two cards</li>
 *        <li>the cards are randomly chosen from decks</li>
 *    </ul>
 */
class BlackjackDealStrategy : public IDealStrategy
{
public:
    virtual ~BlackjackDealStrategy();

    void initialDeal(IGame& game) const;
    virtual void giveCardToPlayer(IGame& game) const;
    virtual void giveCardToDealer(IGame& game) const;
};
