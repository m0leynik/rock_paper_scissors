project(game)

add_executable(game src/main.cpp)
include_directories(../lib/include/)

if (NOT TARGET prs_lib)
    add_subdirectory(../lib build)
endif()

target_link_libraries(game prs_lib)
