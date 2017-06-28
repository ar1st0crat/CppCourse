#include "BlackjackDealStrategy.h"

/**
 * @brief Virtual destructor
 */
BlackjackDealStrategy::~BlackjackDealStrategy()
{
}

/**
 * @brief Method contains logic of initial deal
 * @param game blackjack game
 */
void BlackjackDealStrategy::initialDeal(IGame& game) const
{
    // clear all hands
    game.getDealer()->clearHand();
    game.getPlayer()->clearHand();

    // shuffle and reset decks
    auto decks = game.getDecks();

    uint32_t seed = 10;
    for (auto& deck : decks)
    {
        deck.shuffle(seed);
        seed += 100;
    }
    game.setDecks(decks);

    // the player's given 2 cards
    giveCardToPlayer(game);
    giveCardToPlayer(game);

    // the dealer takes 1 card
    giveCardToDealer(game);
}

/**
 * @brief Method randomly moves a card from deck to player
 * @param game current game
 */
void BlackjackDealStrategy::giveCardToPlayer(IGame& game) const
{
    auto player = game.getPlayer();
    auto decks = game.getDecks();

    // randomly choose the deck and pop the card from that deck
    Card card_from_deck = decks[rand() % decks.size()].popCard();
    // ... and add this card to a Player's hand
    player->addCard(std::move(card_from_deck));
    // don't forget to update decks
    game.setDecks(decks);
}

/**
 * @brief Method randomly moves a card from deck to dealer
 * @param game current game
 */
void BlackjackDealStrategy::giveCardToDealer(IGame& game) const
{
    auto dealer = game.getDealer();
    auto decks = game.getDecks();

    // randomly choose the deck and pop the card from that deck
    Card card_from_deck = decks[rand() % decks.size()].popCard();
    // ... and add this card to a Player's hand
    dealer->addCard(std::move(card_from_deck));
    // don't forget to update decks
    game.setDecks(decks);
}
