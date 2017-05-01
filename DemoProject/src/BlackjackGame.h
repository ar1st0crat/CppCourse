#pragma once

#include <memory>
#include "Player.h"
#include "ICardGame.h"


/** @def The number of decks is 4 */
const size_t DECKS_COUNT = 4;

/** @def The minimal bet equals to 100$ */
const int MIN_BET = 100;


/** @class BlackJackGame
* <p>Represents the BlackJack card game entity</p>
*
* @author ar1st0crat
*/
class BlackjackGame : public ICardGame
{
public:
    BlackjackGame();
    BlackjackGame(std::unique_ptr<IScoreCounter> score_counter);

    bool setup() override;
    void run() override;

protected:
    void shuffle() override;
    void showTable() const override;
    void gameResults() override;

    void dealerActions();
    void setBonuses();

    bool checkEnoughMoney(int money) const;
    bool checkBlackjack(const CardHolder* card_holder) const;
    bool check777(const CardHolder* card_holder) const;
    void playerWins() const noexcept;
    void dealerWins() const noexcept;

protected:
    /** Shoes contain @see DECKS_COUNT decks_ */
    Deck decks_[DECKS_COUNT];
    /** BlackJackGame aggregates the player_ */
    std::shared_ptr<Player> player_;
    /** BlackJackGame is a composite for the dealer_ */
    std::unique_ptr<CardHolder> dealer_;
    /** Object that implements particular score counting strategy */
    std::unique_ptr<IScoreCounter> score_counter_;
};
