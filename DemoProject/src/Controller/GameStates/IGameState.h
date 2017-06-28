#pragma once

#include "../BlackjackController.h"
#include "../PlayerAction.h"

/**
 * @interface IGameState
 * @brief
 */
class IGameState {
public:
    /** Virtual destructor */
    virtual ~IGameState() {}

    /** Method should process player actions in a current state */
    virtual void action(BlackjackController& gameController, PlayerAction player_action) = 0;

    /** Method should contain main logic of being in a current state */
    virtual void update(BlackjackController& gameController) = 0;
};
