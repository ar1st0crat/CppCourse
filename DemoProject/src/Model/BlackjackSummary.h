#pragma once

#include <memory>

/**
 * @struct BlackjackSummary
 * @brief Contains brief info regarding game results
 */
struct BlackjackSummary
{
    bool dealer_blackjack;
    bool player_blackjack;
    bool dealer_bust;
    bool player_bust;
    int32_t player_income;
};
