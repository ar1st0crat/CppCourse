#pragma once

#include "Rules/RuleService.h"
#include "Rules/IDealStrategy.h"
#include "PlayerAction.h"

/**
 * @interface IGameController
 * @brief Interface declares methods for card game controllers
 *
 * @author ar1st0crat
 */
class IGameController
{
public:
    /** Virtual destructor */
    virtual ~IGameController() {}

    /** Method should prepare everything for the game process */
    virtual bool setup() = 0;

    /** Method should contain logic of the entire game process */
    virtual void start() = 0;

    /** Method should contain logic of one particular game */
    virtual void runGame() = 0;

    /** Method should contain logic providing player actions */
    virtual PlayerAction getPlayerAction() const = 0;

    /** Method should update view associated with the game */
    virtual void updateView(const std::string& text = "") const = 0;

    /** Method should provide rules of the game */
    virtual RuleService* getRules() const = 0;

    /** Method should provide the deal strategy of the game */
    virtual IDealStrategy* getDealStrategy() const = 0;
};
