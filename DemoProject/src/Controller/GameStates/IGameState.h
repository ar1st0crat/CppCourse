#pragma once

#include "../BlackjackController.h"
#include "../PlayerAction.h"

/**
 * @interface IGameState
 * @brief Interface declares methods describing the states of a card game
 */
class IGameState {
public:
    /** Virtual destructor */
    virtual ~IGameState() {}

    /** Method should process player actions in the current state of a game */
    virtual void action(BlackjackController& gameController, PlayerAction player_action) = 0;

    /** Method should contain main logic of the game being in a current state */
    virtual void update(BlackjackController& gameController) = 0;
};
