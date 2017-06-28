#include "EarlyBlackjackStrategy.h"

namespace misc
{
    /**
     * @brief Function provides fixed set cards for game participants
     * @return card to give to dealer/player
     */
    Card cardProvider()
    {
        static std::vector<Card> cards = {
                   // cards for initial deal
                   Card(Suit::Clubs, 13), Card(Suit::Clubs, 14),  // to player
                   Card(Suit::Clubs, 14),                         // to dealer
                   // rest
                   Card(Suit::Clubs, 2), Card(Suit::Clubs, 5),
                   Card(Suit::Clubs, 4), Card(Suit::Clubs, 11),
                   Card(Suit::Clubs, 13), Card(Suit::Clubs, 10)
               };

        static int i = 0;

        return cards[(i++) % cards.size()];
    }

    void EarlyBlackjackStrategy::giveCardToPlayer(IGame& game) const
    {
        auto player = game.getPlayer();
        player->addCard(misc::cardProvider());
    }

    void EarlyBlackjackStrategy::giveCardToDealer(IGame& game) const
    {
        auto dealer = game.getDealer();
        dealer->addCard(misc::cardProvider());
    }

    void EarlyBlackjackStrategy::initialDeal(IGame& game) const
    {
        game.getDealer()->clearHand();
        game.getPlayer()->clearHand();

        giveCardToPlayer(game);
        giveCardToPlayer(game);
        giveCardToDealer(game);
    }
}
