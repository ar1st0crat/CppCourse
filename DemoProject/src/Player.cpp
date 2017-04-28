#include "Player.h"


/** Default constructor
* <p>Initializes a player with no money</p>
*/
Player::Player() noexcept
    : money_(0)
{
}

/** Parameterized constructor
* <p>Initializes CardHolder with the name and amount of money given as parameters</p>
* @param [in] const std::string& name the name of a player
* @param [in] int money the amount of player's money  */
Player::Player(const std::string& name, int money) noexcept
    : CardHolder(name), money_(money)
{
}

/** Setter for the player's stake
* @param [in] int stake The stake for gambling */
void Player::setStake(int stake) noexcept
{
    stake_ = stake;
}

/** Method makes player win and increase his/her amount of money by value of the stake */
void Player::winStake() noexcept
{
    money_ += stake_;
}

/** Method increases the player's stake according to a particular coefficient
* @param double coeff   The coefficient for increasing of the player's stake (1.5 by default) */
void Player::bonusStake(double coeff=1.5) noexcept
{
    stake_ *= coeff;
}

/** Method makes player lose and decrease his/her amount of money by value of the stake */
void Player::loseStake() noexcept
{
    money_ -= stake_;
}

/** Method checks whether a player has enough money to double down
* @returns bool true if a player can double down; false - otherwise */
bool Player::canDoubleStake() const noexcept
{
    return stake_ * 2 <= money_;
}

/** Getter for the player's money
* @returns int The player's money */
int Player::getMoney() const noexcept
{
    return money_;
}

/** Getter for the player's stake
* @returns int The player's stake */
int Player::getStake() const noexcept
{
    return stake_;
}

/** Method outputs the amount of player's money */
void Player::showMoney() const noexcept
{
    std::cout << std::endl << "Money " << name_ << ": " << money_ << std::endl;
}
