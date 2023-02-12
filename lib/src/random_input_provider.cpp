#include "random_input_provider.h"

#include <mutex>
#include <random>

namespace {
class RandomInputProvider : public IInputProvider {
public:
    RandomInputProvider() : m_randomShape(0, uint32_t(Shape::ShapesCount) - 1) {
        std::random_device rd;
        m_gen.seed(rd());
    }

    uint32_t GetInput() override {
        std::lock_guard<std::mutex> lock(m_mtx);
        return m_randomShape(m_gen);
    }

private:
    std::mt19937 m_gen;
    std::uniform_int_distribution<std::mt19937::result_type> m_randomShape;
    std::mutex m_mtx;
};
} // namespace

std::shared_ptr<IInputProvider> GetRandonInputProvider() {
    return std::make_shared<RandomInputProvider>();
}
