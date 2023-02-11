#ifndef ___INPUT_PROVIDER_MOCK_H___
#define ___INPUT_PROVIDER_MOCK_H___

#include <gmock/gmock.h>

#include "input_provider_iface.h"

struct InputProviderMock : public IInputProvider {
    MOCK_METHOD0(GetInput, uint32_t());
};

#endif // ___INPUT_PROVIDER_MOCK_H___