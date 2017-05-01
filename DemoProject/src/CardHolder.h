#pragma once

#include <memory>

#include "Deck.h"
#include "BustException.h"
#include "IScoreCounter.h"

/** @class CardHolder
* <p>Represents the CardHolder entity (both the player and the dealer)</p>
*/
class CardHolder
{
public:
    CardHolder() noexcept;
    CardHolder(const std::string& name) noexcept;
    virtual ~CardHolder() noexcept;
     
    std::string getName() const noexcept;
    std::vector<Card> getHand() const noexcept;
    void takeCard(Deck decks[], size_t decks_count);
    void clearHand() noexcept;
    virtual void showHand() const noexcept;

    int countScore(const IScoreCounter* score_counter) const noexcept;

protected:
    /** The name of a cardholder */
    std::string name_;
    /** The hand of a cardholder */
    std::vector<Card> hand_;
};
