#include "prs_lib.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
uint32_t getUintFromArgument(int pos, int argc, char *argv[]) {
    if (pos > argc - 1) {
        throw std::invalid_argument("not enough arguments");
    } else {
        const auto result = std::stol(argv[pos], nullptr);
        if (result <= 0 ) {
            throw std::invalid_argument("unsigned integer expected");
        }
        return result;
    }
}

void showTheRules(std::ostream &outputStream) {
    outputStream << "New round!\n Please, enter your sign:\n" <<
        std::to_string(uint32_t(Shape::Paper)) << " - Paper\n" <<
        std::to_string(uint32_t(Shape::Rock)) << " - Rock\n" <<
        std::to_string(uint32_t(Shape::Scissors)) << " - Scissors";
}

enum class RoundResult : uint32_t { Won, Draw, Lost };

Shape uintToShape(uint32_t input) {

    if (input >= uint32_t(Shape::ShapesCount)) {
        throw std::invalid_argument("cannot convert provided input to shape");
    }

    return Shape(input);
}

RoundResult calculateUserResult(Shape userShape, Shape oponentShape) {
    static RoundResult GameRules [uint32_t(Shape::ShapesCount)][uint32_t(Shape::ShapesCount)] = {
        { RoundResult::Draw, RoundResult::Won, RoundResult::Lost },
        { RoundResult::Lost, RoundResult::Draw, RoundResult::Won },
        { RoundResult::Won, RoundResult::Lost, RoundResult::Draw }
    };

    if ((userShape >= Shape::ShapesCount) || (oponentShape >= Shape::ShapesCount)) {
        throw std::invalid_argument("invalid shape value specified");
    }

    return GameRules[uint32_t(userShape)][uint32_t(oponentShape)];
}

void updateScores(RoundResult roundResult, Scores &scores) {
    switch (roundResult)
    {
    case RoundResult::Won:
        ++scores.user;
        return;
    case RoundResult::Lost:
        ++scores.oponent;
        return;
    case RoundResult::Draw:
        return;
    default:
        throw std::invalid_argument("invalid round result specified");
    }
}
} // namespace

RoundResult PlayRound(IInputProvider &userInputProvider, IInputProvider &oponentInputProvider, std::ostream &outputStream) {
    try
    {
        const auto oponentShape = uintToShape(oponentInputProvider.GetInput());
        const auto userShape = uintToShape(userInputProvider.GetInput());
        return calculateUserResult(userShape, oponentShape);
    }
    catch(const std::exception& e)
    {
        outputStream << e.what() << std::endl;
        // assume round completed in case of exception
        return RoundResult::Draw;
    }
}

Scores PlayGame(uint32_t numRounds, IInputProvider &userInputProvider, IInputProvider &oponentInputProvider, std::ostream &outputStream) {

    Scores scores{};
    for (uint32_t round = 0; round < numRounds; ++round) {
        showTheRules(outputStream);
        const auto roundResults = PlayRound(userInputProvider, oponentInputProvider, outputStream);
        updateScores(roundResults, scores);
    }

    return scores;
}

uint32_t GetNumberOfRounds(int argc, char *argv[]) {
    constexpr int ExpectedArgC = 2;

    if (argc < ExpectedArgC) {
        throw std::invalid_argument("not enough arguments");
    } else if (argc > ExpectedArgC) {
        throw std::invalid_argument("too much arguments");
    } else {
        return getUintFromArgument(1, argc, argv);
    }
}