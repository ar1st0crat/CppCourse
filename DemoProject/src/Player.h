#pragma once

#include "CardHolder.h"

/** @class CardHolder
* <p>Represents the special case of the CardHolder entity (only the persons who gamble stakes)</p>
*
* @author ar1st0crat
*/
class Player : public CardHolder
{
public:
    Player() noexcept;
    Player(const std::string& name, int money) noexcept;

    int getStake() const noexcept;
    void setStake(int stake) noexcept;
    void winStake() noexcept;
    void bonusStake(double coeff) noexcept;
    void loseStake() noexcept;
    bool canDoubleStake() const noexcept;

    void showMoney() const noexcept;
    int getMoney() const noexcept;

protected:
    /** The total amount of player's money */
    int money_;
    /** The player's stake */
    int stake_;
};
