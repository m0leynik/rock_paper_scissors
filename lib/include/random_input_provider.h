#ifndef ___RANDOM_INPUT_PROVIDER_H___
#define ___RANDOM_INPUT_PROVIDER_H___

#include <memory>

#include "input_provider_iface.h"

std::shared_ptr<IInputProvider> GetRandonInputProvider();

#endif // ___RANDOM_INPUT_PROVIDER_H___