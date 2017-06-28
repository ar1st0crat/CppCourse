#pragma once

#include "IGameState.h"

/**
 * @class DealerActionState
 * @brief The state of the game when dealer receives cards
 */
class DealerActionState : public IGameState
{
public:
    void action(BlackjackController& game_controller, PlayerAction player_action) override;
    void update(BlackjackController& game_controller) override;
};
