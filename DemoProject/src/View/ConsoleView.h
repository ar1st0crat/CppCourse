#pragma once

#include "IGameView.h"

/**
 * @class ConsoleView
 * @brief Card game view associated with standard console
 *
 * @author ar1st0crat
 */
class ConsoleView : public IGameView
{
public:
    void output(const std::string& text) const override;
    void outputCardTable(const IGame& game) const override;
    char inputPlayerChoice() const override;
    char inputPlayerWantsToContinue() const override;
    std::string inputPlayerName() const override;
    int32_t inputPlayerStake() const override;
    int32_t inputPlayerMoney() const override;
};
