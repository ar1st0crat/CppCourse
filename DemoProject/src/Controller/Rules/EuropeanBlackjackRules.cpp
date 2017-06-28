#include "EuropeanBlackjackRules.h"

/**
 * @brief Virtual destructor
 */
EuropeanBlackjackRules::~EuropeanBlackjackRules()
{
}

/**
 * @brief Method sets bonuses to player
 * Method sets bonuses for a player under certain circumstances among which are:
 * <ul>
 *   <li>Player's got Blackjack and dealer has more than one card</li>
 *   <li>Player's got Blackjack on the first two cards</li>
 *   <li>Player has 777</li>
 * </ul>
 * @param player player
 * @param dealer dealer
 */
void EuropeanBlackjackRules::bonuses(Player& player, const Player& dealer) const
{
    // no blackjack - no bonuses
    if (!checkBlackjack(player))
    {
        return;
    }
    // if the player has the "777" combination, the player will take one more 1-to-1 bonus
    if (check777(player))
    {
        player.bonusStake(2);
    }
    // if the dealer has more than one card
    // (i.e. the dealer was trying to take more cards in order to repeat the player's blackjack)
    else if (dealer.cardCount() > 1)
    {
        // then the player's winning size should be 3-to-2
        player.bonusStake(1.5);
    }
    // there's also a situation in the very beginning of the game:
    // the dealer's got one card, and the player's got two cards
    // in this case the player takes winning 1-to-1 (i.e. no bonus)
}

/**
 * @brief Method checks if player's got the BlackJack with "777" combination
 * @param player player
 * @return bool true if player's got the "777" combination; false - otherwise
 */
bool EuropeanBlackjackRules::check777(const Player& player) const
{
    if (countScore(player) == 21)
    {
        auto hand = player.getHand();
        if (hand.size() == 3)
        {
            return (hand[0].getRank() == 7 &&
                    hand[1].getRank() == 7 &&
                    hand[2].getRank() == 7);
        }
    }
    return false;
}

/**
 * @brief Method returns the number of decks
 * @return four decks for this type of the game
 */
size_t EuropeanBlackjackRules::deckCount() const
{
    return 4;//decks
}

/**
 * @brief Method checks if player is able to double down
 * @param player player
 * @return true if player's got 9, 10 or 11 (according to the rules of European blackjack), false - otherwise
 */
bool EuropeanBlackjackRules::canDoubleDown(const Player& player) const
{
    // first, check player's money
    if (player.getStake() * 2 > player.getMoney())
    {
        return false;
    }
    // second, check the '9, 10 or 11' condition
    auto score = countScore(player);
    return (score >= 9 || score <= 11);
}
