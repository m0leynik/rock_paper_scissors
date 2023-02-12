project(game)

add_executable(game src/main.cpp)
include_directories(../lib/include/)

if (NOT TARGET game_lib)
    add_subdirectory(../lib build)
endif()

target_link_libraries(game game_lib)
