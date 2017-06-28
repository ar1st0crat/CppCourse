#include "DealerActionState.h"
#include "GameOverState.h"
#include <iostream>

/**
 * @brief DealerActionState::update
 * <p>The dealer takes cards while his/her total score is less than 17</p>
 * @param game
 */
void DealerActionState::update(BlackjackController& game_controller)
{
    auto game = game_controller.getGame();
    auto rules = game_controller.getRules();
    auto deal = game_controller.getDealStrategy();
    auto dealer = game->getDealer();
    auto summary = game->getSummary();

    auto score = rules->countScore(*dealer);

    while (score < rules->minimalDealerScore())
    {
        deal->giveCardToDealer(*game);
        score = rules->countScore(*dealer);
    }

    if (rules->checkBust(*dealer))
    {
        summary.dealer_bust = true;
        game->updateSummary(summary);
    }
    else if (rules->checkBlackjack(*dealer))
    {
        summary.dealer_blackjack = true;
        game->updateSummary(summary);
    }

    game_controller.switchState(new GameOverState);
}

void DealerActionState::action(BlackjackController& game_controller,
                               PlayerAction player_action)
{
}
