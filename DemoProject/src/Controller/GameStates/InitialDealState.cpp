#include "InitialDealState.h"
#include "PlayerActionState.h"
#include "EarlyBlackjackState.h"

void InitialDealState::update(BlackjackController& game_controller)
{
    auto game = game_controller.getGame();
    auto rules = game_controller.getRules();
    auto deal = game_controller.getDealStrategy();
    auto player = game->getPlayer();
    auto summary = game->getSummary();

    deal->initialDeal(*game);

    if (rules->checkBlackjack(*player))
    {
        summary.player_blackjack = true;
        game->updateSummary(summary);

        game_controller.updateView();
        game_controller.updateView(player->getName() + " blackjack\n");

        game_controller.switchState(new EarlyBlackjackState);
    }
    else
    {
        game_controller.switchState(new PlayerActionState);
    }
}

void InitialDealState::action(BlackjackController& game_controller,
                              PlayerAction player_action)
{
}
