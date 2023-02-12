#ifndef ___CONSOLE_INPUT_PROVIDER_H___
#define ___CONSOLE_INPUT_PROVIDER_H___

#include <memory>

#include "input_provider_iface.h"

std::shared_ptr<IInputProvider> GetConsoleInputProvider();

#endif // ___CONSOLE_INPUT_PROVIDER_H___