#include "BlackjackController.h"
#include "Rules/BlackjackDealStrategy.h"
#include "Rules/EuropeanBlackjackRules.h"
#include "GameStates/InitialDealState.h"
#include "GameStates/GameOverState.h"
#include "../View/ConsoleView.h"

/**
 * @brief Constructor with three optional injections
 * @param view associated view of the game
 * @param deal deal strategy of the game
 * @param rules rules of the game
 */
BlackjackController::BlackjackController
                        (std::unique_ptr<IGameView> view,
                         std::unique_ptr<IDealStrategy> deal,
                         std::unique_ptr<RuleService> rules)
    : game_(std::make_unique<BlackjackGame>())
{
    if (view == nullptr)
    {
        view_ = std::make_unique<ConsoleView>();
    }
    else
    {
        view_ = std::move(view);
    }

    if (deal == nullptr)
    {
        deal_ = std::make_unique<BlackjackDealStrategy>();
    }
    else
    {
        deal_ = std::move(deal);
    }

    if (rules == nullptr)
    {
        rules_ = std::make_unique<EuropeanBlackjackRules>();
    }
    else
    {
        rules_ = std::move(rules);
    }

    game_->setDecks(std::vector<Deck>(rules_->deckCount()));
}

/**
 * @brief Virtual destructor
 */
BlackjackController::~BlackjackController()
{
}

/**
 * @brief Method sets up game (creates player and dealer)
 * @return true if player's got enough money to play, false - otherwise
 */
bool BlackjackController::setup()
{
    auto player_name = view_->inputPlayerName();
    auto money = view_->inputPlayerMoney();

    if (!rules_->checkEnoughMoney(money))
    {
        view_->output("You don't have enough money to continue playing!");
        return false;
    }

    // we're ready to go, so create player and dealer
    game_->setPlayer(player_name, money);
    game_->setDealer("Dealer");

    return true;
}

/**
 * @brief Method contains main logic of the game process
 */
void BlackjackController::start()
{
    if (!setup())
    {
        return;
    }

    auto answer = 'y';
    // keep asking player to play until he/she wishes to continue
    while (answer == 'y')
    {
        // ========== preparations for a new game

        // reset summary
        game_->updateSummary({});

        // gamble stake
        auto player = game_->getPlayer();
        auto min_stake = rules_->minimalStake();

        auto stake = view_->inputPlayerStake();

        while (stake < min_stake || stake > player->getMoney())
        {
            if (stake < min_stake)
            {
                view_->output("Your stake should be at least " + std::to_string(min_stake) + "$");
            }
            if (stake > player->getMoney())
            {
                view_->output("You don't have enough money!");
            }
            stake = view_->inputPlayerStake();
        }

        player->setStake(stake);

        // ******* start new game *******
        runGame();
        // ******************************

        // show player's money after this (already completed) shuffle
        view_->output("\nMoney " + player->getName() + ": " + std::to_string(player->getMoney()));

        // check if player has enough money to continue
        if (!rules_->checkEnoughMoney(player->getMoney()))
        {
            view_->output("You don't have enough money to continue playing!");
            return;
        }
        answer = view_->inputPlayerWantsToContinue();
    }
}

/**
 * @brief Method contains logic of one particular game
 * The main logic is State-based
 */
void BlackjackController::runGame()
{
    // put the game in the 'initial deal' state
    switchState(new InitialDealState);

    // go on until the game reaches the 'game over' state
    // (yes, in C++ dynamic_cast looks quite ugly)
    while (!dynamic_cast<GameOverState*>(state_.get()))
    {
        state_->action(*this, getPlayerAction());
    }
}

/**
 * @brief Method provides player actions
 * @return PlayerAction player's current action
 */
PlayerAction BlackjackController::getPlayerAction() const
{
    auto action = view_->inputPlayerChoice();
    return static_cast<PlayerAction>(action - 0x31);
}

/**
 * @brief Method updates view associated with the game
 * @param text text to present
 */
void BlackjackController::updateView(const std::string& text) const
{
    if (text == "")
    {
        view_->outputCardTable(*getGame());
    }
    else
    {
        view_->output(text);
    }
}

/**
 * @brief Method changes the state of a game (participates in State pattern)
 * @param state  game state to switch to
 */
void BlackjackController::switchState(IGameState* state)
{
    state_.reset(state);
    state_->update(*this);
}

BlackjackGame *BlackjackController::getGame() const
{
    return game_.get();
}

RuleService* BlackjackController::getRules() const
{
    return rules_.get();
}

IDealStrategy* BlackjackController::getDealStrategy() const
{
    return deal_.get();
}
