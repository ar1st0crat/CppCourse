#pragma once

#include "../IDealStrategy.h"

namespace misc
{
    class EarlyBlackjackStrategy : public IDealStrategy
    {
    public:
        void giveCardToPlayer(IGame& game) const override;
        void giveCardToDealer(IGame& game) const override;
        void initialDeal(IGame& game) const override;
    };
}
