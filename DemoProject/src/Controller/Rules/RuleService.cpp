#include "RuleService.h"

/**
 * @brief Method implements the score counting strategy
 * @param player player
 * @return total score of cards in player's hand
 */
uint8_t RuleService::countScore(const Player& player) const
{
    auto hand = player.getHand();
    auto score = 0;

    // the number of aces in the hand to be counted as 11 ("11-aces")
    auto aces = 0;

    // count each card in the hand
    for (auto& card : hand)
    {
        auto rank = card.getRank();
        // set the value of J, Q, K equal to 10
        if (rank > 10)
        {
            // if we're dealing with Ace then first we increase the total score by 11
            // and increase the number of 11-aces in the hand (by default)
            if (rank == 14)
            {
                rank = 11;
                aces++;
            }
            else
            {
                rank = 10;
            }
        }
        score += rank;
    }
    // if we got so many aces that we got busted then try to count one ace as 1 (not as 11)
    // and decrease the number of "11-aces"
    while (score > blackjackScore() && aces > 0)
    {
        score -= 10;
        aces--;
    }
    return score;
}

uint8_t RuleService::blackjackScore() const
{
    return 21;
}

bool RuleService::checkBlackjack(const Player& player) const
{
    return countScore(player) == blackjackScore();
}

bool RuleService::checkBust(const Player& player) const
{
    return countScore(player) > blackjackScore();
}

uint8_t RuleService::minimalDealerScore() const
{
    return 17;
}

size_t RuleService::deckCount() const
{
    return 2;//decks
}

int32_t RuleService::minimalStake() const
{
    return 100;//$
}

/**
 * @brief Method checks player's money (it should be enough for the minimal bet)
 * @param money amount of player's money
 * @return true if player's got enough money, false - otherwise
 */
bool RuleService::checkEnoughMoney(int32_t money) const
{
    return (money >= minimalStake());
}
