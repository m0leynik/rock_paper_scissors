#include "game_lib.h"

#include <iostream>

namespace {
void printHelp(std::ostream &out) {
    out << "Hello from the Papaer-Rock-Scissors game!\n"
        "The only argument is the number of rounds.\n"
        "For example run:\n"
        "./game 6\n"
        "to play 6-round-game\n";
}

void showTotalScores(const Scores &scores, std::ostream &out) {
    out << "Total scores:" << std::endl
        << "Yours: " << scores.user << std::endl
        << "Oponent's: " << scores.oponent << std::endl;
}
} // namespace

int main(int argc, char *argv[]) {
    std::ostream &out = std::cout;
    try
    {
        const auto numRounds = GetNumberOfRounds(argc, argv);
        const auto scores = PlayGame(numRounds, *GetConsoleInputProvider(), *GetRandonInputProvider(), out);
        showTotalScores(scores, out);
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        printHelp(out);
        return 1;
    }
}