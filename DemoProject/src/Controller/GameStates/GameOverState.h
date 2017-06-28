#pragma once

#include "IGameState.h"

/**
 * @class GameOverState
 * @brief Ending state of the game (time to analyze results and create summary)
 */
class GameOverState : public IGameState
{
public:
    void action(BlackjackController& game_controller, PlayerAction player_action) override;
    void update(BlackjackController& game_controller) override;

private:
    void playerWins(BlackjackController& game_controller) const;
    void playerLoses(BlackjackController& game_controller) const;
    void playerTie(BlackjackController& game_controller) const;
};
