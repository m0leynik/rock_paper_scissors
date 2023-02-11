project(test)

include(../cmake/google_benchmark.cmake)

enable_testing()
add_executable(test src/main.cpp src/game_test.cpp src/input_provider_mock.h)
include_directories(../lib/include/ ./include)

if (NOT TARGET prs_lib)
    add_subdirectory(../lib build)
endif()

target_link_libraries(test prs_lib gmock_main)
