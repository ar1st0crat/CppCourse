#include "PlayerActionState.h"
#include "DealerActionState.h"
#include "GameOverState.h"
#include <iostream>

void PlayerActionState::action(BlackjackController& game_controller,
                               PlayerAction player_action)
{
    auto game = game_controller.getGame();
    auto rules = game_controller.getRules();
    auto player = game->getPlayer();
    auto deal = game_controller.getDealStrategy();
    auto summary = game->getSummary();

    switch (player_action)
    {
        case PlayerAction::DOUBLE:
        {
            if (rules->canDoubleDown(*player))
            {
                player->bonusStake(2);
            }
            else
            {
                game_controller.updateView("You can't double down!");
                update(game_controller);
                break;
            }
        }
        case PlayerAction::HIT:
        {
            deal->giveCardToPlayer(*game);

            if (rules->checkBust(*player))
            {
                summary.player_bust = true;
                game->updateSummary(summary);

                game_controller.switchState(new GameOverState);
            }
            else if (rules->checkBlackjack(*player))
            {
                summary.player_blackjack = true;
                game->updateSummary(summary);

                game_controller.switchState(new DealerActionState);
            }
            else
            {
                update(game_controller);
            }
            break;
        }
        case PlayerAction::STAND:
        {
            game_controller.switchState(new DealerActionState);
        }
    }
}

void PlayerActionState::update(BlackjackController& game_controller)
{
    auto game = game_controller.getGame();
    auto rules = game_controller.getRules();
    auto player = game->getPlayer();

    game_controller.updateView();

    game_controller.updateView("1. Hit");
    game_controller.updateView("2. Stand");
    if (rules->canDoubleDown(*player))
    {
        game_controller.updateView("3. Double");
    }
}
