#pragma once

#include <memory>
#include "RuleService.h"

/**
 * @class EuropeanBlackjackRules
 * @brief Particular rule service providing rules for European blackjack
 */
class EuropeanBlackjackRules : public RuleService
{
public:
    virtual ~EuropeanBlackjackRules();
    void bonuses(Player& player, const Player& dealer) const override;
    bool check777(const Player& player) const;
    bool canDoubleDown(const Player& player) const override;
    size_t deckCount() const override;
};
