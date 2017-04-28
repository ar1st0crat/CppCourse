#include <gtest/gtest.h>
#include "../src/BlackjackScoreCounter.h"
#include <iostream>


BlackjackScoreCounter counter;

TEST(ScoreCounterTest, TestTwoAces)
{
	// ARRANGE
	std::vector<Card> cards = { Card(Suit::Clubs, 12), Card(Suit::Clubs, 12) };
	// ACT
	int score = counter.countScore(cards);
	// ASSERT
	ASSERT_EQ(score, 12);
}

TEST(ScoreCounterTest, TestEmptyDeck)
{
	// ARRANGE
	std::vector<Card> cards;
	// ACT
	int score = counter.countScore(cards);
	// ASSERT
	ASSERT_EQ(score, 0);
}

TEST(ScoreCounterTest, TestAceAndKing)
{
	// ARRANGE
	std::vector<Card> cards = { Card(Suit::Clubs, 11), Card(Suit::Clubs, 12) };
	// ACT
	int score = counter.countScore(cards);
	// ASSERT
	ASSERT_EQ(score, 21);
}

TEST(ScoreCounterTest, TestAceAndTwoKings)
{
	// ARRANGE
	std::vector<Card> cards = { Card(Suit::Clubs, 11), Card(Suit::Clubs, 11), Card(Suit::Clubs, 12) };
	// ACT
	int score = counter.countScore(cards);
	// ASSERT
	ASSERT_EQ(score, 21);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
