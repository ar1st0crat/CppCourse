#include "GameOverState.h"
#include <iostream>

void GameOverState::update(BlackjackController& game_controller)
{
    auto game = game_controller.getGame();
    auto rules = game_controller.getRules();
    auto player = game->getPlayer();
    auto dealer = game->getDealer();
    auto summary = game->getSummary();

    game_controller.updateView();

    if (summary.player_bust)
    {
        game_controller.updateView(player->getName() + " bust");
        playerLoses(game_controller);
    }
    else if (summary.dealer_bust)
    {
        game_controller.updateView("Dealer bust\n");
        rules->bonuses(*player, *dealer);
        playerWins(game_controller);
    }
    else
    {
        // compare total scores of the dealer and the player
        auto player_score = rules->countScore(*player);
        auto dealer_score = rules->countScore(*dealer);

        if (player_score < dealer_score)
        {
            playerLoses(game_controller);
        }
        else if (player_score == dealer_score)
        {
            playerTie(game_controller);
        }
        else
        {
            // maybe we should set bonuses to the player
            rules->bonuses(*player, *dealer);
            playerWins(game_controller);
        }
    }

    summary.player_income = player->getStake();
    game->updateSummary(summary);
}

void GameOverState::action(BlackjackController& game_controller,
                           PlayerAction player_action)
{
}

/**
 * @brief Method is called when player wins
 */
void GameOverState::playerWins(BlackjackController& game_controller) const
{
    auto game = game_controller.getGame();
    auto player = game->getPlayer();
    auto summary = game->getSummary();

    auto text = player->getName() + " wins";
    if (summary.player_blackjack)
    {
        text += " with blackjack";
    }

    game_controller.updateView(text);
    game_controller.updateView("The winning size: " + std::to_string(player->getStake()));
    player->winStake();
}

/**
 * @brief Method is called when dealer wins
 */
void GameOverState::playerLoses(BlackjackController& game_controller) const
{
    auto game = game_controller.getGame();
    auto player = game->getPlayer();
    auto summary = game->getSummary();

    auto text = player->getName() + " loses to dealer";
    if (summary.dealer_blackjack)
    {
        text += " with blackjack";
    }

    game_controller.updateView(text);
    game_controller.updateView("Losing size: " + std::to_string(player->getStake()));
    player->loseStake();
}

/**
 * @brief Method is called when the game ended up in tie (push)
 */
void GameOverState::playerTie(BlackjackController& game_controller) const
{
    auto game = game_controller.getGame();
    auto player = game->getPlayer();
    auto summary = game->getSummary();

    if (summary.dealer_blackjack)
    {
        game_controller.updateView(player->getName() + " blackjack");
        game_controller.updateView("Dealer blackjack");
    }

    game_controller.updateView("\nPush (tie)");
    player->setStake(0);
}
