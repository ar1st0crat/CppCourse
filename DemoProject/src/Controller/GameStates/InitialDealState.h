#pragma once

#include "IGameState.h"

/**
 * @class InitialDealState
 * @brief The state of the game when the first cards are given to dealer and player
 */
class InitialDealState : public IGameState
{
public:
    void action(BlackjackController& gameController, PlayerAction player_action) override;
    void update(BlackjackController& gameController) override;
};

