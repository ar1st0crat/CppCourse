#include "mocks.h"

// ****************************************************************
// ======= SIMPLE TEST SUITE : Card score in player's hand ========
// ****************************************************************

EuropeanBlackjackRules rules;

TEST(ScoreCounterTest, testTwoAces)
{
    // ARRANGE
    Player player("test");
    player.addCard(Card(Suit::Clubs, 14));
    player.addCard(Card(Suit::Clubs, 14));
    // ACT
    auto score = rules.countScore(player);
    // ASSERT
    ASSERT_EQ(score, 12);
}

TEST(ScoreCounterTest, testEmptyHand)
{
    // ARRANGE
    Player player("test");
    // ACT
    auto score = rules.countScore(player);
    // ASSERT
    ASSERT_EQ(score, 0);
}

TEST(ScoreCounterTest, testAceAndKing)
{
    // ARRANGE
    Player player("test");
    player.addCard(Card(Suit::Clubs, 13));
    player.addCard(Card(Suit::Clubs, 14));
    // ACT
    auto score = rules.countScore(player);
    // ASSERT
    ASSERT_EQ(score, 21);
}

TEST(ScoreCounterTest, testAceAndTwoKings)
{
    // ARRANGE
    Player player("test");
    player.addCard(Card(Suit::Clubs, 13));
    player.addCard(Card(Suit::Clubs, 13));
    player.addCard(Card(Suit::Clubs, 14));
    // ACT
    auto score = rules.countScore(player);
    // ASSERT
    ASSERT_EQ(score, 21);
}

TEST(ScoreCounterTest, testTwoAcesAndTwoKings)
{
    // ARRANGE
    Player player("test");
    player.addCard(Card(Suit::Clubs, 13));
    player.addCard(Card(Suit::Clubs, 13));
    player.addCard(Card(Suit::Clubs, 14));
    player.addCard(Card(Suit::Clubs, 14));
    // ACT
    auto score = rules.countScore(player);
    // ASSERT
    ASSERT_EQ(score, 22);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
