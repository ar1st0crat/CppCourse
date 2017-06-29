#pragma once

#include "../../Model/Player.h"

/**
 * @abstract RuleService
 * @brief An abstract class whose purpose is providing the rules of a game
 *
 * Rules of the game include:
 * <ul>
 *   <li>technique for calculating the total score on a Player's hand</li>
 *   <li>check for blackjack, bust and other outcomes of the game</li>
 *   <li>technique for calculating bonuses for players</li>
 *   <li>number of decks and minimally required player's bet</li>
 * </ul>
 *
 * @author ar1st0crat
 */
class RuleService
{
public:
    /** Virtual destructor */
    virtual ~RuleService() {}

    /** Method should return blackjack score (i.e. 21, except some exotic cases) */
    virtual uint8_t blackjackScore() const;

    /** Method should calculate the total score in player's hand) */
    virtual uint8_t countScore(const Player& player) const;

    /** Method should check if player got blackjack */
    virtual bool checkBlackjack(const Player& player) const;

    /** Method should check if player is busted */
    virtual bool checkBust(const Player& player) const;

    /** Method should check if player is able to double down */
    virtual bool canDoubleDown(const Player& player) const = 0;

    /** Method should set bonuses to player */
    virtual void bonuses(Player& player, const Player& dealer) const = 0;

    /** Method should return number of points sufficient for dealer to stop taking cards */
    virtual uint8_t minimalDealerScore() const;

    /** Method should return the number of decks used in game */
    virtual size_t deckCount() const;

    /** Method should return the minimally required stake from player */
    virtual int32_t minimalStake() const;

    /** Method should check if player's got enough money to continue  */
    virtual bool checkEnoughMoney(int32_t money) const;
};
