#include "Card.h"   

/**
 * @brief Default Card constructor
 * Initializes card with rank=2 and suit=Clubs (creates the card 2♣)
 */
Card::Card() : Card(Suit::Clubs, 2)
{
}

/**
 * @brief Parameterized constructor
 * Initializes Card with given rank and suit</p>
 */
Card::Card(Suit suit, uint8_t rank) : suit_(suit), rank_(rank), face_up_(true)
{
}

/**
 * @brief Gets the ordinal number of a Card
 * Method automatically evaluates correct ordinal number of the Card based on its rank and suit
 * @return The ordinal number of a Card
 */
size_t Card::getNumber() const
{
    return static_cast<int>(suit_) * 13 + rank_ - 2;
}

/**
 * @brief Sets the ordinal number of a Card
 * Method automatically evaluates correct suit and rank of the Card
 * @param card_no The ordinal number of a Card
 */
void Card::setNumber(size_t card_no)
{
    suit_ = static_cast<Suit>(card_no / 13);
    rank_ = card_no % 13 + 2; 
}

uint8_t Card::getRank() const
{
    return rank_;
}

Suit Card::getSuit() const
{
    return suit_;
}

/**
 * @brief Method flips card face up or face down
 * @param face_up true if face up, false if face down
 */
void Card::flip(bool face_up)
{
    face_up_ = face_up;
}
