#include "prs_lib.h"

#include <iostream>

namespace {
void printHelp() {
    std::cout << "Hello from the Papaer-Rock-Scissors game!\n"
        "The only argument is the number of rounds.\n"
        "For example run:\n"
        "./game 6\n"
        "to play 6-round-game";
}
} // namespace

int main(int argc, char *argv[]) {
    try
    {
        const auto numRounds = GetNumberOfRounds(argc, argv);
        const auto results = PlayGame(numRounds, *GetConsoleInputProvider(), *GetRandonInputProvider(), std::cout);
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        printHelp();
        return 1;
    }
}