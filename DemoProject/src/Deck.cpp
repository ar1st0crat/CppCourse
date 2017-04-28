#include <algorithm>
#include "Deck.h"


/** The default constructor unpacks new deck */
Deck::Deck() noexcept
{
    unpackNew();
}

/** The method emulates unpacking of a new deck (generates ordered set of cards from 2♥ to A♠) */
void Deck::unpackNew() noexcept
{
    cards_.resize(DECK_SIZE);
    int pos = 0;
    // let's take a look at c++11 lambdas:
    // generate cards (with numbers from 0 to DECK_SIZE - 1)
    std::for_each(begin(cards_), end(cards_), [&pos](Card& card) 
        {
            card.setNumber(pos++); 
        });
}

/** The method pops the top card from the deck
* @return Card the top card in the deck */
Card Deck::popCard()
{
    // here we could have an exception but in fact a deck will never become empty
    Card c = cards_.back();
    cards_.pop_back();

    return c;
}

/** The method returns the number of cards in the deck
* @return int number of cards in the deck */
int Deck::getCardsCount() const noexcept
{
    return cards_.size();
}


/** The method calls Deck::unpackNew() method first and then shuffles randomly cards in the deck
* @param [in] unsigned int seed   The seed for randomizing (is added to the current time)
*/
void Deck::shuffle(unsigned int seed) noexcept
{
    unpackNew();
    std::srand(seed + std::time(0));
    std::random_shuffle(begin(cards_), end(cards_));
}
