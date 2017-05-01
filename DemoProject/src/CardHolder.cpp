#include "CardHolder.h"

/** Default constructor
* <p>Initializes CardHolder with the name "Unknown"</p>
*/
CardHolder::CardHolder() noexcept
    : name_("Unknown")
{
}

/** Parameterized constructor
* <p>Initializes CardHolder with the name given as a parameter</p>
* @param [in] const std::string& name The name of a cardholder
*/
CardHolder::CardHolder(const std::string& name) noexcept
    : name_(name)
{
}

/** Virtual destructor */
CardHolder::~CardHolder() noexcept
{
}

/** Getter for the name of a cardholder
* @returns std::string the name of a cardholder
*/
std::string CardHolder::getName() const noexcept
{
    return name_;
}

/** Getter for the hand of a cardholder 
* @returns std::vector<Card> The hand of a cardholder
*/
std::vector<Card> CardHolder::getHand() const noexcept
{
    return hand_;
}

/** Method shows all cards in a cardholder's hand */
void CardHolder::showHand() const noexcept
{
    std::cout << name_ << "\t";          // first the cardholder's name
    std::cout << hand_ << std::endl;     // then the overloaded output method for a cardholder's hand
}

/** Default constructor
* <p>Initializes Card with rank=2 and suit=Clubs (creates a card 2♣)</p>
* @param [in] Deck decks[]  The array of decks to randomly choose from for picking a card
* @param [in] size_t decks_count  The number of decks
*/
void CardHolder::takeCard(Deck decks[], size_t decks_count)
{
    // we randomly choose the deck and pop the card from that deck
    Card card_from_deck = decks[rand() % decks_count].popCard();
    // ... and add this card to a cardholder's hand
    hand_.emplace_back(std::move(card_from_deck));
}

/** Method removes all cards from a cardholder's hand */
void CardHolder::clearHand() noexcept
{
    hand_.clear();
}

/** Method delegates the task of score counting to its scoreCounter object
* @param [in] const IScoreCounter& score_counter An object that implements particular score counting strategy
* @returns the total score of a cardholder's hand */
int CardHolder::countScore(const IScoreCounter* score_counter) const noexcept
{
    return score_counter->countScore(hand_);
}
