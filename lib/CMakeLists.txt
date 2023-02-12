project(game_lib)

include_directories(./include/)

add_library(game_lib 
        src/game_lib.cpp include/game_lib.h
        src/input_provider.cpp include/input_provider.h include/input_provider_iface.h
)