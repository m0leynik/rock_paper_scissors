project(prs_lib)

include_directories(./include/)

add_library(prs_lib 
        src/prs_lib.cpp include/prs_lib.h
        src/input_provider.cpp include/input_provider.h include/input_provider_iface.h
)