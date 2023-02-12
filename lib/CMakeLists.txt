project(game_lib)

include_directories(./include/)

add_library(game_lib 
        src/game_lib.cpp include/game_lib.h
        include/input_provider_iface.h
        src/random_input_provider.cpp include/random_input_provider.h
        src/console_input_provider.cpp include/console_input_provider.h 
)