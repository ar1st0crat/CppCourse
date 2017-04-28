#pragma once

#include <ctime>
#include <algorithm>
#include <vector>

#include "Card.h"

/** @def DECK_SIZE 
* <p> 52 (The size of a deck by default)</p> */
const size_t DECK_SIZE = 52; 


/** @class Deck
* <p>Represents the Deck of Cards entity</p>
*
* @author ar1st0crat
*/
class Deck
{
public:
    Deck() noexcept;
    
    Card popCard();
    int getCardsCount() const noexcept;
    void unpackNew() noexcept;
    void shuffle(unsigned int seed) noexcept;

protected:
    /** cards in the deck (vector of Card) */
    std::vector<Card> cards_;
};
