#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <vector>

#include "../src/Controller/BlackjackController.h"
#include "../src/Model/BlackjackGame.h"
#include "../src/Controller/Rules/EuropeanBlackjackRules.h"


using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InSequence;
using ::testing::AtLeast;
using ::testing::HasSubstr;
using ::testing::_;


/**
 * @brief Mock for classes implementing IGameView interface
 */
class MockView : public IGameView
{
public:
    MOCK_CONST_METHOD1(output, void(const std::string&));
    MOCK_CONST_METHOD1(outputCardTable, void(const IGame&));
    MOCK_CONST_METHOD0(inputPlayerWantsToContinue, char());
    MOCK_CONST_METHOD0(inputPlayerChoice, char());
    MOCK_CONST_METHOD0(inputPlayerName, std::string());
    MOCK_CONST_METHOD0(inputPlayerStake, int32_t());
    MOCK_CONST_METHOD0(inputPlayerMoney, int32_t());

    /**
     * @brief Method sets common expectations for a view
     * @param choices player choices as vector of chars ('1', '2', '1', etc.)
     */
    void prepareView(std::vector<char>& choices)
    {
        ON_CALL(*this, inputPlayerName()).WillByDefault(Return("test"));
        ON_CALL(*this, inputPlayerMoney()).WillByDefault(Return(1000));
        ON_CALL(*this, inputPlayerStake()).WillByDefault(Return(100));
        ON_CALL(*this, inputPlayerWantsToContinue()).WillByDefault(Return('n'));
        // sequentially provide mocking player choices
        {
            InSequence seq;
            for (auto& choice : choices)
                EXPECT_CALL(*this, inputPlayerChoice()).WillOnce(Return(choice));
        }
    }
};


/**
 * @brief Mock for classes implementing IDealStrategy interface
 */
class MockStrategy : public IDealStrategy
{
public:
    MOCK_CONST_METHOD1(initialDeal, void(IGame& game));
    MOCK_CONST_METHOD1(giveCardToPlayer, void(IGame& game));
    MOCK_CONST_METHOD1(giveCardToDealer, void(IGame& game));

    /**
     * @brief Method sets common expectations for particular deal
     * @param initial_cards vector of cards in initial deal
     * @param dealer_cards vector of cards to be given to dealer
     * @param player_cards vector of cards to be given to player
     */
    void prepareDeal(std::vector<Card>& initial_cards,
                     std::vector<Card>& dealer_cards,
                     std::vector<Card>& player_cards)
    {
        ON_CALL(*this, initialDeal(_))
                .WillByDefault(
                    Invoke([&initial_cards](IGame& game) {
                                     game.getDealer()->addCard(std::move(initial_cards[0]));
                                     game.getPlayer()->addCard(std::move(initial_cards[1]));
                                     game.getPlayer()->addCard(std::move(initial_cards[2]));
                                 }));

        // Give cards to the dealer 1-by-1 from testing card set
        {
            InSequence seq;
            for (auto& card : dealer_cards)
                EXPECT_CALL(*this, giveCardToDealer(_))
                        .WillOnce(Invoke([&card](IGame& game) {
                                      game.getDealer()->addCard(std::move(card));
                                  }));
        }
        // Give cards to the player 1-by-1 from testing card set
        {
            InSequence seq;
            for (auto& card : player_cards)
                EXPECT_CALL(*this, giveCardToPlayer(_))
                        .WillOnce(Invoke([&card](IGame& game) {
                                      game.getPlayer()->addCard(std::move(card));
                                  }));
        }
    }
};
