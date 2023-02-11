#include <array>

#include <gtest/gtest.h>

#include "prs_lib.h"
#include "input_provider_mock.h"

namespace {
    std::ostream &TestOstream = std::cout;
}

TEST(GameTest, GetTimesToPlay_Succeeded)
{
    constexpr int argc = 2;
    char* argv[argc] = { const_cast<char*>("exe"), const_cast<char*>("666") };
    const auto numRounds = GetNumberOfRounds(argc, argv);

    ASSERT_EQ(numRounds, 666);
}

TEST(GameTest, GetTimesToPlay_ThrowsOnNegativeIntegerInput)
{
    constexpr int argc = 2;
    char* argv[argc] = { const_cast<char*>("exe"), const_cast<char*>("-555") };

    ASSERT_THROW(GetNumberOfRounds(argc, argv), std::invalid_argument);
}

TEST(GameTest, GetTimesToPlay_ThrowsOnInvalidInput)
{
    constexpr int argc = 2;
    char* argv[argc] = { const_cast<char*>("exe"), const_cast<char*>("asfasf") };
    
    ASSERT_THROW(GetNumberOfRounds(argc, argv), std::invalid_argument);
}

TEST(GameTest, PlayGame_NoScoresWhenTheInputIsSame)
{
    constexpr uint32_t NumRounds = 6;
    const auto userInputProvider = std::make_unique<InputProviderMock>();
    const auto oponentInputProvider = std::make_unique<InputProviderMock>();

    auto sameInput = [&]() {
        return uint32_t(Shape::Rock);
    };

    EXPECT_CALL(*userInputProvider, GetInput()).Times(NumRounds).WillRepeatedly(sameInput);
    EXPECT_CALL(*oponentInputProvider, GetInput()).Times(NumRounds).WillRepeatedly(sameInput);

    const auto scores = PlayGame(NumRounds, *userInputProvider, *oponentInputProvider, TestOstream);
    ASSERT_EQ(0, scores.user);
    ASSERT_EQ(scores.oponent, scores.user);
}

TEST(GameTest, PlayGame_PaperWrapsRock)
{
    constexpr uint32_t NumRounds = 6;
    const auto userInputProvider = std::make_unique<InputProviderMock>();
    const auto oponentInputProvider = std::make_unique<InputProviderMock>();

    auto userInput = [&]() {
        return uint32_t(Shape::Paper);
    };
    auto oponentInput = [&]() {
        return uint32_t(Shape::Rock);
    };
    EXPECT_CALL(*userInputProvider, GetInput()).Times(NumRounds).WillRepeatedly(userInput);
    EXPECT_CALL(*oponentInputProvider, GetInput()).Times(NumRounds).WillRepeatedly(oponentInput);

    const auto scores = PlayGame(NumRounds, *userInputProvider, *oponentInputProvider, TestOstream);
    ASSERT_EQ(NumRounds, scores.user);
    ASSERT_EQ(0, scores.oponent);
}

TEST(GameTest, PlayGame_RockBreaksScissors)
{
    constexpr uint32_t NumRounds = 6;
    const auto userInputProvider = std::make_unique<InputProviderMock>();
    const auto oponentInputProvider = std::make_unique<InputProviderMock>();

    auto userInput = [&]() {
        return uint32_t(Shape::Rock);
    };
    auto oponentInput = [&]() {
        return uint32_t(Shape::Scissors);
    };
    EXPECT_CALL(*userInputProvider, GetInput()).Times(NumRounds).WillRepeatedly(userInput);
    EXPECT_CALL(*oponentInputProvider, GetInput()).Times(NumRounds).WillRepeatedly(oponentInput);

    const auto scores = PlayGame(NumRounds, *userInputProvider, *oponentInputProvider, TestOstream);
    ASSERT_EQ(NumRounds, scores.user);
    ASSERT_EQ(0, scores.oponent);
}

TEST(GameTest, PlayGame_ScissorsCutPaper)
{
    constexpr uint32_t NumRounds = 6;
    const auto userInputProvider = std::make_unique<InputProviderMock>();
    const auto oponentInputProvider = std::make_unique<InputProviderMock>();

    auto userInput = [&]() {
        return uint32_t(Shape::Paper);
    };
    auto oponentInput = [&]() {
        return uint32_t(Shape::Scissors);
    };
    EXPECT_CALL(*userInputProvider, GetInput()).Times(NumRounds).WillRepeatedly(userInput);
    EXPECT_CALL(*oponentInputProvider, GetInput()).Times(NumRounds).WillRepeatedly(oponentInput);

    const auto scores = PlayGame(NumRounds, *userInputProvider, *oponentInputProvider, TestOstream);
    ASSERT_EQ(NumRounds, scores.oponent);
    ASSERT_EQ(0, scores.user);
}

TEST(GameTest, PlayGame_ScoresCalculatedCorrectlyOnSingleInputMistake)
{
    constexpr uint32_t NumRounds = 6;
    const auto userInputProvider = std::make_unique<InputProviderMock>();
    const auto oponentInputProvider = std::make_unique<InputProviderMock>();

    auto userInput = [&]() {
        return uint32_t(Shape::Paper);
    };
    auto oponentInput = [&]() {
        static size_t callCount = 0;
        callCount++;
        if (callCount == (NumRounds/2)) {
            return uint32_t(666);
        }
        return uint32_t(Shape::Scissors);
    };
    EXPECT_CALL(*userInputProvider, GetInput()).WillRepeatedly(userInput);
    EXPECT_CALL(*oponentInputProvider, GetInput()).WillRepeatedly(oponentInput);

    const auto scores = PlayGame(NumRounds, *userInputProvider, *oponentInputProvider, TestOstream);
    ASSERT_EQ(NumRounds - 1, scores.oponent);
    ASSERT_EQ(0, scores.user);
}

TEST(GameTest, PlayGame_NoScoresOnMistakesDuringAllTheRounds)
{
    constexpr uint32_t NumRounds = 6;
    const auto userInputProvider = std::make_unique<InputProviderMock>();
    const auto oponentInputProvider = std::make_unique<InputProviderMock>();

    auto userInput = [&]() {
        return uint32_t(Shape::Paper);
    };
    auto invalidInput = [&]() {
        return uint32_t(666);
    };
    EXPECT_CALL(*userInputProvider, GetInput()).WillRepeatedly(userInput);
    EXPECT_CALL(*oponentInputProvider, GetInput()).WillRepeatedly(invalidInput);

    const auto scores = PlayGame(NumRounds, *userInputProvider, *oponentInputProvider, TestOstream);
    ASSERT_EQ(scores.user, scores.oponent);
    ASSERT_EQ(0, scores.user);
}