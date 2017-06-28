#include "mocks.h"

// ****************************************************************
// =========  TEST SUITE 2 : Early Blackjack situations  ==========
// ****************************************************************

/**
 * @brief Early blackjack scenario when player agrees to take money right away:
 *
 *      Initial deal:
 *          dealer:     A♣
 *          player:     K♣ A♣
 *
 *      View should show options (Keep playing or take 1-to-1 winning)
 *
 *      Player should choose option '2' (Take 1-to-1 win)
 *
 *      Stake: 100$   ->    Player should win 100$
 */
TEST(EarlyBlackjack, testPlayerTakesWinning1To1)
{
    // ARRANGE view
    auto view = std::make_unique<NiceMock<MockView>>();

    std::vector<char> player_choices = {'2'};

    view->prepareView(player_choices);

    // ARRANGE deal
    auto deal = std::make_unique<NiceMock<MockStrategy>>();

    std::vector<Card> initial_cards = {Card(Suit::Clubs, 14), Card(Suit::Clubs, 13), Card(Suit::Clubs, 14)};
    std::vector<Card> dealer_cards = {};
    std::vector<Card> player_cards = {};

    deal->prepareDeal(initial_cards, dealer_cards, player_cards);

    // EXPECT
    EXPECT_CALL(*view, output(_)).Times(AtLeast(1));
    EXPECT_CALL(*view, output(HasSubstr("1. Keep playing"))).Times(1);

    // ACT
    BlackjackController controller(std::move(view), std::move(deal));
    controller.start();

    // ASSERT
    auto summary = controller.getGame()->getSummary();

    ASSERT_EQ(summary.player_blackjack, true);
    ASSERT_EQ(summary.player_income, 100);
}

/**
 * @brief Early blackjack scenario when player keeps playing and ends up with push (tie):
 *
 *      Initial deal:
 *          dealer:     A♣
 *          player:     K♣ A♣
 *
 *      Player should choose option '1' (Keep playing)
 *
 *      Dealer should be given:
 *          dealer:     Q♣
 *
 *      Game should end with push (tie)
 *
 *      Stake: 100$   ->    Player should neither win nor lose (0$)
 */
TEST(EarlyBlackjack, testPlayerKeepsPlayingAndTie)
{
    // ARRANGE view
    auto view = std::make_unique<NiceMock<MockView>>();

    std::vector<char> player_choices = {'1'};

    view->prepareView(player_choices);

    // ARRANGE deal
    auto deal = std::make_unique<NiceMock<MockStrategy>>();

    std::vector<Card> initial_cards = {Card(Suit::Clubs, 14), Card(Suit::Clubs, 13), Card(Suit::Clubs, 14)};
    std::vector<Card> dealer_cards = {Card(Suit::Clubs, 12)};
    std::vector<Card> player_cards = {};

    deal->prepareDeal(initial_cards, dealer_cards, player_cards);

    // ACT
    BlackjackController controller(std::move(view), std::move(deal));
    controller.start();

    // ASSERT
    auto summary = controller.getGame()->getSummary();

    ASSERT_EQ(summary.dealer_blackjack, true);
    ASSERT_EQ(summary.player_blackjack, true);
    ASSERT_EQ(summary.player_income, 0);
}

/**
 * @brief Early blackjack scenario when player keeps playing and eventually wins:
 *
 *      Initial deal:
 *          dealer:     A♣
 *          player:     K♣ A♣
 *
 *      Player should choose option '1' (Keep playing)
 *
 *      Dealer should be given:
 *          dealer:     7♣
 *
 *      Stake: 100$   ->   Player should win 150$
 */
TEST(EarlyBlackjack, testPlayerKeepsPlayingAndWins)
{
    // ARRANGE view
    auto view = std::make_unique<NiceMock<MockView>>();

    std::vector<char> player_choices = {'1'};

    view->prepareView(player_choices);

    // ARRANGE deal
    auto deal = std::make_unique<NiceMock<MockStrategy>>();

    std::vector<Card> initial_cards = {Card(Suit::Clubs, 14), Card(Suit::Clubs, 13), Card(Suit::Clubs, 14)};
    std::vector<Card> dealer_cards = {Card(Suit::Clubs, 7)};
    std::vector<Card> player_cards = {};

    deal->prepareDeal(initial_cards, dealer_cards, player_cards);

    // ACT
    BlackjackController controller(std::move(view), std::move(deal));
    controller.start();

    // ASSERT
    auto summary = controller.getGame()->getSummary();

    ASSERT_EQ(summary.player_blackjack, true);
    ASSERT_EQ(summary.player_income, 150);
}

/**
 * @brief Early blackjack scenario when dealer's given cards and eventually gets busted:
 *
 *      Initial deal:
 *          dealer:     Q♣
 *          player:     K♣ A♣
 *
 *      No options should be shown!
 *
 *      Dealer should be given:
 *          dealer:     2♣ 3♣ 10♣
 *
 *      Stake: 100$   ->   Player should win 150$
 */
TEST(EarlyBlackjack, testDealerPlaysAndLoses)
{
    // ARRANGE view
    auto view = std::make_unique<NiceMock<MockView>>();

    std::vector<char> player_choices = {};

    view->prepareView(player_choices);

    // ARRANGE deal
    auto deal = std::make_unique<NiceMock<MockStrategy>>();

    std::vector<Card> initial_cards = {Card(Suit::Clubs, 12), Card(Suit::Clubs, 13), Card(Suit::Clubs, 14)};
    std::vector<Card> dealer_cards = {Card(Suit::Clubs, 2), Card(Suit::Clubs, 3), Card(Suit::Clubs, 10)};
    std::vector<Card> player_cards = {};

    deal->prepareDeal(initial_cards, dealer_cards, player_cards);

    // EXPECT
    EXPECT_CALL(*view, output(_)).Times(AtLeast(1));
    EXPECT_CALL(*view, output(HasSubstr("1. Keep playing"))).Times(0);

    // ACT
    BlackjackController controller(std::move(view), std::move(deal));
    controller.start();

    // ASSERT
    auto summary = controller.getGame()->getSummary();

    ASSERT_EQ(summary.player_blackjack, true);
    ASSERT_EQ(summary.dealer_bust, true);
    ASSERT_EQ(summary.player_income, 150);
}
