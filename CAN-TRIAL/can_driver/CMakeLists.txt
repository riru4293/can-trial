cmake_minimum_required( VERSION 3.12 )

project( can_driver
    VERSION 1.0.0
    DESCRIPTION "CAN driver manager"
    LANGUAGES CXX C ASM
)

add_library( can_driver STATIC
    ./src/mcp2515.c
)

target_compile_features( can_driver PRIVATE cxx_std_11 )

target_include_directories( can_driver PUBLIC include )

target_link_libraries( can_driver
    PRIVATE pico_stdlib
    PRIVATE spi_wrapper
)
