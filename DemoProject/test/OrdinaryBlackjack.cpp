#include "mocks.h"

// ****************************************************************
// =======  TEST SUITE 3 : Ordinary Blackjack situations  =========
// ****************************************************************

/**
 * @brief Ordinary blackjack scenario when player takes cards and gets busted:
 *
 *      Initial deal:
 *          dealer:     Q♣
 *          player:     7♣ 3♣
 *
 *      Options for player actions should be shown.
 *
 *      Player should choose repeatedly:
 *          1. Hit      (and should be given 5♣)
 *          1. Hit      (and should be given 9♣)
 *
 *      Dealer should be given nothing, the game should stop right away.
 *
 *      Game summary should indicate that player got busted.
 *
 *      Stake: 100$   ->   player should lose 100$.
 */
TEST(OrdinaryBlackjack, testPlayerGetsBusted)
{
    // ARRANGE view
    auto view = std::make_unique<NiceMock<MockView>>();

    std::vector<char> player_choices = {'1', '1'};

    view->prepareView(player_choices);

    // ARRANGE deal
    auto deal = std::make_unique<NiceMock<MockStrategy>>();

    std::vector<Card> initial_cards = {Card(Suit::Clubs, 12), Card(Suit::Clubs, 7), Card(Suit::Clubs, 3)};
    std::vector<Card> dealer_cards = {};
    std::vector<Card> player_cards = {Card(Suit::Clubs, 5), Card(Suit::Clubs, 9)};

    deal->prepareDeal(initial_cards, dealer_cards, player_cards);

    // EXPECT that dealer doesn't even come in play
    EXPECT_CALL(*deal, giveCardToDealer(_)).Times(0);

    // ACT
    BlackjackController controller(std::move(view), std::move(deal));
    controller.start();

    // ASSERT
    auto summary = controller.getGame()->getSummary();

    ASSERT_EQ(summary.player_income, -100);
    ASSERT_EQ(summary.player_bust, true);
}

/**
 * @brief Ordinary blackjack scenario when player has 7 7 7:
 *
 *      Initial deal:
 *          dealer:     Q♣
 *          player:     7♣ 7♣
 *
 *      Options for player actions should be shown.
 *
 *      Player should choose:
 *          1. Hit      (and should be given 7♣)
 *
 *      Dealer should be given 10♣
 *
 *      Game summary should indicate that player got blackjack.
 *
 *      Stake: 100$   ->   player should win 200$.
 */
TEST(OrdinaryBlackjack, testPlayerGets777)
{
    // ARRANGE view
    auto view = std::make_unique<NiceMock<MockView>>();

    std::vector<char> player_choices = {'1'};

    view->prepareView(player_choices);

    // ARRANGE deal
    auto deal = std::make_unique<NiceMock<MockStrategy>>();

    std::vector<Card> initial_cards = {Card(Suit::Clubs, 12), Card(Suit::Clubs, 7), Card(Suit::Clubs, 7)};
    std::vector<Card> dealer_cards = {Card(Suit::Clubs, 10)};
    std::vector<Card> player_cards = {Card(Suit::Clubs, 7)};

    deal->prepareDeal(initial_cards, dealer_cards, player_cards);

    // ACT
    BlackjackController controller(std::move(view), std::move(deal));
    controller.start();

    // ASSERT
    auto summary = controller.getGame()->getSummary();

    ASSERT_EQ(summary.player_blackjack, true);
    ASSERT_EQ(summary.player_income, 200);
}

/**
 * @brief Ordinary blackjack scenario when player chooses to double down and wins blackjack:
 *
 *      Initial deal:
 *          dealer:     Q♣
 *          player:     2♣ 6♣
 *
 *      Options for player actions should be shown.
 *
 *      Player should choose:
 *          3. Double      (and should be given 5♣)
 *          1. Hit         (and should be given 8♣)
 *
 *      Dealer should be given 10♣
 *
 *      Game summary should indicate that player got blackjack.
 *
 *      Stake: 100$   ->   player should win 300$.
 */
TEST(OrdinaryBlackjack, testPlayerBlackjackAfterDoubleDown)
{
    // ARRANGE view
    auto view = std::make_unique<NiceMock<MockView>>();

    std::vector<char> player_choices = {'3', '1'};

    view->prepareView(player_choices);

    // ARRANGE deal
    auto deal = std::make_unique<NiceMock<MockStrategy>>();

    std::vector<Card> initial_cards = {Card(Suit::Clubs, 12), Card(Suit::Clubs, 2), Card(Suit::Clubs, 6)};
    std::vector<Card> dealer_cards = {Card(Suit::Clubs, 10)};
    std::vector<Card> player_cards = {Card(Suit::Clubs, 5), Card(Suit::Clubs, 8)};

    deal->prepareDeal(initial_cards, dealer_cards, player_cards);

    // ACT
    BlackjackController controller(std::move(view), std::move(deal));
    controller.start();

    // ASSERT
    auto summary = controller.getGame()->getSummary();

    ASSERT_EQ(summary.player_blackjack, true);
    ASSERT_EQ(summary.player_income, 300);
}

/**
 * @brief Ordinary scenario when player takes cards and then stops:
 *
 *      Initial deal:
 *          dealer:     Q♣
 *          player:     2♣ 6♣
 *
 *      Options for player actions should be shown.
 *
 *      Player should choose:
 *          1. Hit      (and should be given 3♣)
 *          1. Hit      (and should be given 8♣)
 *          2. Stand
 *
 *      Dealer should be given 7♣
 *
 *      Stake: 100$   ->   player should win 100$.
 */
TEST(OrdinaryBlackjack, testPlayerTakesCardsAndStops)
{
    // ARRANGE view
    auto view = std::make_unique<NiceMock<MockView>>();

    std::vector<char> player_choices = {'1', '1', '2'};

    view->prepareView(player_choices);

    // ARRANGE deal
    auto deal = std::make_unique<NiceMock<MockStrategy>>();

    std::vector<Card> initial_cards = {Card(Suit::Clubs, 12), Card(Suit::Clubs, 2), Card(Suit::Clubs, 6)};
    std::vector<Card> dealer_cards = {Card(Suit::Clubs, 7)};
    std::vector<Card> player_cards = {Card(Suit::Clubs, 3), Card(Suit::Clubs, 8)};

    deal->prepareDeal(initial_cards, dealer_cards, player_cards);

    // ACT
    BlackjackController controller(std::move(view), std::move(deal));
    controller.start();

    // ASSERT
    auto summary = controller.getGame()->getSummary();

    ASSERT_EQ(summary.player_income, 100);
}

/**
 * @brief Ordinary scenario when player takes cards, doubles, stops and eventually loses:
 *
 *      Initial deal:
 *          dealer:     Q♣
 *          player:     2♣ 6♣
 *
 *      Options for player actions should be shown.
 *
 *      Player should choose:
 *          1. Hit      (and should be given 3♣)
 *          3. Double   (and should be given 8♣)
 *          2. Stand
 *
 *      Dealer should be given 10♣
 *
 *      Stake: 100$   ->   player should lose 200$.
 */
TEST(OrdinaryBlackjack, testPlayerTakesCardsAndStopsThenLoses)
{
    // ARRANGE view
    auto view = std::make_unique<NiceMock<MockView>>();

    std::vector<char> player_choices = {'1', '3', '2'};

    view->prepareView(player_choices);

    // ARRANGE deal
    auto deal = std::make_unique<NiceMock<MockStrategy>>();

    std::vector<Card> initial_cards = {Card(Suit::Clubs, 12), Card(Suit::Clubs, 2), Card(Suit::Clubs, 6)};
    std::vector<Card> dealer_cards = {Card(Suit::Clubs, 10)};
    std::vector<Card> player_cards = {Card(Suit::Clubs, 3), Card(Suit::Clubs, 8)};

    deal->prepareDeal(initial_cards, dealer_cards, player_cards);

    // ACT
    BlackjackController controller(std::move(view), std::move(deal));
    controller.start();

    // ASSERT
    auto summary = controller.getGame()->getSummary();

    ASSERT_EQ(summary.player_income, -200);
}
