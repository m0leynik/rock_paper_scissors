#ifndef ___INPUT_PROVIDER_IFACE_H___
#define ___INPUT_PROVIDER_IFACE_H___

#include <cstdint>

enum class Shape : uint32_t { 
    Paper, 
    Rock, 
    Scissors, 
    
    ShapesCount 
};

struct IInputProvider {
    virtual uint32_t GetInput() = 0;
    virtual ~IInputProvider(){}
};

#endif // ___INPUT_PROVIDER_IFACE_H___