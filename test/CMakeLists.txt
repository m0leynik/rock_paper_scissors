project(test)

include(../cmake/google_benchmark.cmake)

enable_testing()
add_executable(test src/main.cpp src/game_test.cpp src/input_provider_mock.h)
include_directories(../lib/include/ ./include)

if (NOT TARGET game_lib)
    add_subdirectory(../lib build)
endif()

target_link_libraries(test game_lib gmock_main)
