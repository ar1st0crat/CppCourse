#include "Card.h"   

/** Default constructor
* <p>Initializes Card with rank=2 and suit=Clubs (creates a card 2♣)</p>
*/
Card::Card() noexcept
    : suit_(Suit::Clubs), rank_(2) 
{
}

/** Parameterized constructor
* <p>Initializes Card with given rank and suit</p>
* @param[in] suit The suit a card to create
* @param[in] card_no The ordinal number of a card to create */
Card::Card(Suit suit, size_t card_no) noexcept
    : suit_(suit), rank_(card_no % 13 + 2)
{
}

/** Gets the ordinal number of a Card
* <p>Method automatically evaluates correct ordinal number of the Card based on its rank and suit</p>
* @returns The ordinal number of a Card */
size_t Card::getNumber() const noexcept
{
    return static_cast<int>(suit_) * 13 + rank_ - 2;
}

/** Getter for the rank of Card
* @returns The rank of a Card */
short Card::getRank() const noexcept
{
    return rank_;
}

/** Sets the ordinal number of a Card
* <p>Method automatically evaluates correct suit and rank of the Card</p>
* @param[in] size_t card_no The ordinal number of a Card */
void Card::setNumber(size_t card_no) noexcept
{
    suit_ = static_cast<Suit>(card_no / 13);
    rank_ = card_no % 13 + 2; 
}

/** Overloaded output operator for a Card
* @param[in] std::ostream& os   Reference to an output stream
* @param[in] const Card& card   Reference to a Card object to output
* @returns Reference to an output stream (for further using it in output chains) */
std::ostream& operator<<(std::ostream& os, const Card& card)
{
    static std::string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

#ifdef __linux__
    static std::string suit_symbols[] = { "\u2665", "\u2666", "\u2663", "\u2660" };
#else
    static std::string suit_symbols[] = { "\x03", "\x04", "\x05", "\x06" };
#endif

    os << ranks[card.rank_ - 2] << suit_symbols[static_cast<int>(card.suit_)];

    return os;
}

/** Overloaded output operator for a Hand
* @param[in] std::ostream& os  Reference to an output stream
* @param[in] const std::vector<Card>& hand  Reference to vector of cards to output
* @return Reference to an output stream (for further using it in output chains) */
std::ostream& operator<<(std::ostream& os, const std::vector<Card>& hand)
{
    for (auto& card : hand)
    {
        os << card << " ";
    }
    return os;
}
