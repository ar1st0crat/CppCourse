#pragma once

#include <string>
#include "../Model/IGame.h"

/**
 * @interface IGameView
 * @brief Declares methods for card game views
 *
 * @author ar1st0crat
 */
class IGameView
{
public:
    /** Virtual destructor */
    virtual ~IGameView() {}

    /** Plain text output */
    virtual void output(const std::string& text) const = 0;

    /** Show entire card table */
    virtual void outputCardTable(const IGame& game) const = 0;

    /** Input player's choice for different actions */
    virtual char inputPlayerChoice() const = 0;

    /** Input player's answer if he/she wishes to play again */
    virtual char inputPlayerWantsToContinue() const = 0;

    /** Input player's name */
    virtual std::string inputPlayerName() const = 0;

    /** Input player's stake */
    virtual int32_t inputPlayerStake() const = 0;

    /** Input amount of player's money */
    virtual int32_t inputPlayerMoney() const = 0;
};
