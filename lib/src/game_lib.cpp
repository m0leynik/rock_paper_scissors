#include "game_lib.h"

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
            throw std::invalid_argument("positive integer expected");
        }
        return result;
    }
}

std::array<std::string, size_t(Shape::ShapesCount)> ShapeToString = {
    "Paper", "Rock", "Scissors"
};

void showTheRules(std::ostream &out) {
    static const std::string Rules = std::string("New round!\n") +
        "Please, enter your sign:\n" +
        std::to_string(uint32_t(Shape::Paper)) + " - " + ShapeToString[size_t(Shape::Paper)] + "\n" +
        std::to_string(uint32_t(Shape::Rock)) + " - " + ShapeToString[size_t(Shape::Rock)] + "\n" +
        std::to_string(uint32_t(Shape::Scissors)) + " - " + ShapeToString[size_t(Shape::Scissors)] + "\n";
    
    out << Rules;
}

Shape uintToShape(uint32_t input) {

    if (input >= uint32_t(Shape::ShapesCount)) {
        throw std::invalid_argument("cannot convert provided input to shape");
    }

    return Shape(input);
}

enum class RoundResult : uint32_t { Won, Draw, Lost };

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

std::string_view RoundResultToString(RoundResult roundResult) {
    
    if (roundResult == RoundResult::Won) { 
        return "Won :)";
    } else if (roundResult == RoundResult::Draw) {
        return "Draw :|";
    } else if (roundResult == RoundResult::Lost) {
        return "Lost :(";
    } else {
        throw std::invalid_argument("invalid round result specified");
    }
}

void showRoundResults(RoundResult roundResult, Shape userShape, Shape oponentShape, const Scores &scores, std::ostream &out) {

    out << "Your shape is " << ShapeToString[uint32_t(userShape)] << std::endl
        << "Oponent's shape is " << ShapeToString[uint32_t(oponentShape)] << std::endl
        << std::endl
        << RoundResultToString(roundResult) << std::endl
        << std::endl
        << "Scores" << std::endl
        << "Yours: " << scores.user << std::endl
        << "Oponent's: " << scores.oponent << std::endl;
}

void playRound(IInputProvider &userInputProvider, IInputProvider &oponentInputProvider, Scores &scores, std::ostream &out) {
    try
    {
        const auto userShape = uintToShape(userInputProvider.GetInput());
        const auto oponentShape = uintToShape(oponentInputProvider.GetInput());
        
        const auto roundResult = calculateUserResult(userShape, oponentShape);
        updateScores(roundResult, scores);
        showRoundResults(roundResult, userShape, oponentShape, scores, out);
    }
    catch(const std::exception& e)
    {
        // assume round completed in case of exception
        out << e.what() << std::endl;
    }
}
} // namespace

Scores PlayGame(uint32_t numRounds, IInputProvider &userInputProvider, IInputProvider &oponentInputProvider, std::ostream &out) {

    Scores scores{};
    for (uint32_t round = 0; round < numRounds; ++round) {
        showTheRules(out);
        playRound(userInputProvider, oponentInputProvider, scores, out);
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