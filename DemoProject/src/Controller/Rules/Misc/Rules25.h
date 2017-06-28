#pragma once

#include "../EuropeanBlackjackRules.h"

namespace misc
{
    class Rules25 : public EuropeanBlackjackRules
    {
    public:
        uint8_t blackjackScore() const override
        {
            return 25;
        }

        uint8_t minimalDealerScore() const override
        {
            return 20;
        }
    };
}
