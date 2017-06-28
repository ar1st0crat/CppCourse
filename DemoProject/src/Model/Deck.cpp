#include <algorithm>
#include <ctime>
#include "Deck.h"

/**
 * @brief Default constructor
 * Unpacks new deck
 */
Deck::Deck()
{
    unpackNew();
}

/**
 * @brief Method emulates unpacking of a new deck
 * (generates ordered set of cards from 2♥ to A♠)
 */
void Deck::unpackNew()
{
    cards_.resize(DECK_SIZE);
    auto pos = 0;
    // let's take a look at c++11 lambdas:
    // generate cards (with numbers from 0 to DECK_SIZE - 1)
    std::for_each(begin(cards_), end(cards_), [&pos](Card& card) 
        {
            card.setNumber(pos++); 
        });
}

/**
 * @brief Method pops the top card from the deck
 * @return The top card in the deck
 */
Card Deck::popCard()
{
    // here we could have an exception but in fact a deck will never become empty
    auto top_card = cards_.back();
    cards_.pop_back();
    return top_card;
}

/**
 * @brief Method returns the number of cards in the deck
 * @return Number of cards in the deck
 */
size_t Deck::cardCount() const
{
    return cards_.size();
}

/**
 * @brief Method calls Deck::unpackNew() method first and then shuffles randomly cards in the deck
 * @param seed The seed for randomizing (is added to the current time)
 */
void Deck::shuffle(uint32_t seed)
{
    unpackNew();
    std::srand(seed + std::time(0));
    std::random_shuffle(begin(cards_), end(cards_));
}
