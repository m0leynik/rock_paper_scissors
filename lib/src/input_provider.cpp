#include "input_provider.h"

#include <random>
#include <iostream>

namespace {
class RandomInputProvider : public IInputProvider {
public:
    RandomInputProvider() : m_randomShape(0, uint32_t(Shape::ShapesCount) - 1) {
        std::random_device rd;
        m_gen.seed(rd());
    }

    uint32_t GetInput() override {
        return m_randomShape(m_gen);
    }

private:
    std::mt19937 m_gen;
    std::uniform_int_distribution<std::mt19937::result_type> m_randomShape;
};

uint32_t GetUserInputFromConsole() {
    uint32_t result = 0;
    std::cin >> result;
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

std::shared_ptr<IInputProvider> GetRandonInputProvider() {
    return std::make_shared<RandomInputProvider>();
}

std::shared_ptr<IInputProvider> GetConsoleInputProvider() {
    return std::make_shared<ConsoleInputProvider>();
}
