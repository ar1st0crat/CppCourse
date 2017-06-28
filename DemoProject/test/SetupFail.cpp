#include "mocks.h"

// ****************************************************************
// ==========  TEST SUITE 1 : Failed Setup situations  ============
// ****************************************************************

/**
 * @brief Failed setup scenario when player's got not enough money
 *
 * Assert that controller's setup() returns false
 */
TEST(TestSetupFail, testSetupReturnsFalse)
{
    // ARRANGE view
    auto view = std::make_unique<NiceMock<MockView>>();

    ON_CALL(*view, inputPlayerMoney()).WillByDefault(Return(20));

    BlackjackController fail_setup_controller(std::move(view));

    // ACT and ASSERT setup returns false
    ASSERT_EQ(fail_setup_controller.setup(), false);
}

/**
 * @brief Failed setup scenario when player's got not enough money
 *
 * Expect that view never asks player to input his/her stake
 * (i.e. controller never starts new game)
 */
TEST(TestSetupFail, testGameNeverStarts)
{
    // ARRANGE view
    auto view = std::make_unique<NiceMock<MockView>>();

    ON_CALL(*view, inputPlayerMoney()).WillByDefault(Return(20));


    // EXPECT controller to stop after unsuccessful setup
    //        and never ask player to enter his/her stake
    EXPECT_CALL(*view, inputPlayerStake()).Times(0);


    // ACT
    BlackjackController fail_setup_controller(std::move(view));
    fail_setup_controller.setup();
}
