#pragma once

#include "IGameState.h"

/**
 * @class PlayerActionState
 * @brief The state of the game when player makes his/her moves
 */
class PlayerActionState : public IGameState
{
public:
    void action(BlackjackController& game_controller, PlayerAction player_action) override;
    void update(BlackjackController& game_controller) override;
};
