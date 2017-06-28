#pragma once

#include <vector>
#include "Card.h"

/**
 * @class Deck
 * @brief Represents the 'Deck of сards' entity
 *
 * @author ar1st0crat
 */
class Deck
{
public:
    Deck();
    
    Card popCard();
    size_t cardCount() const;
    void unpackNew();
    void shuffle(uint32_t seed);

protected:
    /** cards in the deck */
    std::vector<Card> cards_;

private:
    /** @def DECK_SIZE
     *  52 (The size of a deck by default) */
    static const size_t DECK_SIZE = 52;
};
