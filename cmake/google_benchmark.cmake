include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1)

#FetchContent_Declare(googlebenchmark
#        GIT_REPOSITORY https://github.com/google/benchmark.git
#        GIT_TAG v1.6.0) # need master for benchmark::benchmark

FetchContent_MakeAvailable(
        googletest
#        googlebenchmark
)
