#pragma once

#include <memory>
#include "IGameController.h"
#include "../Model/BlackjackGame.h"
#include "../View/IGameView.h"

class IGameState;

/**
 * @class BlackjackController
 * @brief Blackjack game controller
 *
 * It is also the 'Context' in terms of State design pattern
 *
 * @author ar1st0crat
 */
class BlackjackController : public IGameController
{
public:
    BlackjackController(std::unique_ptr<IGameView> view = nullptr,
                   std::unique_ptr<IDealStrategy> deal = nullptr,
                   std::unique_ptr<RuleService> rules = nullptr);
    virtual ~BlackjackController();

    bool setup() override;
    void start() override;
    void runGame() override;

    PlayerAction getPlayerAction() const override;
    void updateView(const std::string& text = "") const override;

    RuleService* getRules() const override;
    IDealStrategy* getDealStrategy() const override;
    BlackjackGame* getGame() const;

protected:
    /** game under control */
    std::unique_ptr<BlackjackGame> game_;
    /** associated view */
    std::unique_ptr<IGameView> view_;
    /** rules of the game */
    std::unique_ptr<RuleService> rules_;
    /** logic of the deal */
    std::unique_ptr<IDealStrategy> deal_;

// "State pattern"-related members
public:
    void switchState(IGameState *state);
private:
    /** Current state of the game */
    std::unique_ptr<IGameState> state_;
};
