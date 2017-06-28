#include "EarlyBlackjackState.h"
#include "DealerActionState.h"
#include "GameOverState.h"
#include <iostream>

void EarlyBlackjackState::action(BlackjackController& game_controller,
                                 PlayerAction player_action)
{
    switch (player_action)
    {
        case PlayerAction::HIT:
        {
            game_controller.switchState(new DealerActionState);
            break;
        }
        case PlayerAction::STAND:
        {
            game_controller.switchState(new GameOverState);
            break;
        }
    }
}

void EarlyBlackjackState::update(BlackjackController& game_controller)
{
    auto game = game_controller.getGame();
    auto rules = game_controller.getRules();
    auto dealer = game->getDealer();

    auto score = rules->countScore(*dealer);

    if (score == 10)
    {
        game_controller.switchState(new DealerActionState);
    }
    // if the dealer's got Ace...
    else if (score == 11)
    {
        // ...then (according to rules) we can suggest player two following options:

        game_controller.updateView("1. Keep playing");                // option 1 (HIT)
        game_controller.updateView("2. Take the winning 1 to 1");     // option 2 (STAND)
    }
    else
    {
        game_controller.switchState(new GameOverState);
    }
}
