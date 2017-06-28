#pragma once

#include "IGameState.h"

/**
 * @class EarlyBlackjackState
 * @brief Specific state of the game when player gets blackjack right after initial deal
 */
class EarlyBlackjackState : public IGameState
{
public:
    void action(BlackjackController& game_controller, PlayerAction player_action) override;
    void update(BlackjackController& game_controller) override;
};
