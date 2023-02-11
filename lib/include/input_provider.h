#ifndef ___INPUT_PROVIDER_H___
#define ___INPUT_PROVIDER_H___

#include <memory>

#include "input_provider_iface.h"

std::shared_ptr<IInputProvider> GetRandonInputProvider();
std::shared_ptr<IInputProvider> GetConsoleInputProvider();

#endif // ___INPUT_PROVIDER_H___