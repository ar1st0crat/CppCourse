#include "Player.h"

/**
 * @brief Default constructor
 * Initializes "unknown" player with no money
 */
Player::Player() : name_("unknown"), money_(0)
{
}

/**
 * @brief Parameterized constructor
 * Initializes Player with the name and amount of money given as parameters
 * @param name the name of a player
 * @param money the amount of player's money
 */
Player::Player(const std::string& name, int32_t money)
    : name_(name), money_(money)
{
}

/**
 * @brief Method returns number of cards in Player's hand
 * @return number of cards
 */
size_t Player::cardCount() const
{
    return hand_.size();
}

/**
 * @brief Method moves a given card from deck to Player's hand
 * @param card card from the deck
 */
void Player::addCard(Card&& card)
{
    hand_.emplace_back(card);
}

/**
 * @brief Method removes all cards from a Player's hand
 */
void Player::clearHand()
{
    hand_.clear();
}

/**
 * @brief Method makes player win and increase his/her amount of money by value of the stake
 */
void Player::winStake()
{
    money_ += stake_;
}

/**
 * @brief Method increases the player's stake according to a particular coefficient
 * @param coeff The coefficient for increasing of the player's stake (1.5 by default)
 */
void Player::bonusStake(double coeff)
{
    stake_ *= coeff;
}

/**
 * @brief Method makes player lose and decrease his/her amount of money by value of the stake
 * Note: method affects player's stake
 */
void Player::loseStake()
{
    stake_ = -stake_;
    money_ += stake_;
}

/**
 * @brief Method checks whether a player has enough money to double down
 * @return true if a player can double down; false - otherwise
 */
bool Player::canDoubleStake() const
{
    return stake_ * 2 <= money_;
}

std::string Player::getName() const
{
    return name_;
}

std::vector<Card> Player::getHand() const
{
    return hand_;
}

int32_t Player::getMoney() const
{
    return money_;
}

int32_t Player::getStake() const
{
    return stake_;
}

void Player::setStake(int32_t stake)
{
    stake_ = stake;
}
