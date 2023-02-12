#include "console_input_provider.h"

#include <iostream>

namespace {
uint32_t GetUserInputFromConsole() {
    std::string input{};
    std::cin >> input;

    const auto result = std::stol(input, nullptr);
    if (result < 0 ) {
        throw std::invalid_argument("unsigned integer expected");
    }
    return result;
}

class ConsoleInputProvider : public IInputProvider {
public:
    ConsoleInputProvider() = default;

    uint32_t GetInput() override {
        return GetUserInputFromConsole();
    }
};
} // namespace

std::shared_ptr<IInputProvider> GetConsoleInputProvider() {
    return std::make_shared<ConsoleInputProvider>();
}
