#ifndef ___PRS_LIB_H___
#define ___PRS_LIB_H___

#include <functional>
#include <optional>
#include <string>

#include <input_provider.h>

struct Scores{
    uint32_t user;
    uint32_t oponent;
};

Scores PlayGame(uint32_t numRounds, IInputProvider &userInputProvider, IInputProvider &oponentInputProvider, std::ostream &out);
uint32_t GetNumberOfRounds(int argc, char *argv[]);

#endif // ___PRS_LIB_H___