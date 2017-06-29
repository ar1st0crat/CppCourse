#pragma once

#include <memory>
#include "Card.h"

/**
 * @class Player
 * @brief Represents card game participants (both players and dealers)
 *
 * @author ar1st0crat
 */
class Player
{
public:
    Player();
    Player(const std::string& name, int32_t money=0);

    size_t cardCount() const;
    void addCard(Card &&card);
    void clearHand();

    void winStake();
    void bonusStake(double coeff=1.5);
    void loseStake();
    bool canDoubleStake() const;

    std::string getName() const;
    std::vector<Card> getHand() const;
    int32_t getMoney() const;
    int32_t getStake() const;
    void setStake(int32_t stake);

protected:
    /** Player's name */
    std::string name_;
    /** Player's hand */
    std::vector<Card> hand_;
    /** Total amount of player's money */
    int32_t money_;
    /** Player's current stake (becomes negative when player loses) */
    int32_t stake_;
};
