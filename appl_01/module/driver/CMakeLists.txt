cmake_minimum_required(VERSION 3.14)

# Set module name
set(MOD_NAME "driver")

project(${MOD_NAME} VERSION 1.0.0
    DESCRIPTION "Hardware drivers"
    LANGUAGES CXX C ASM
)

add_library(${MOD_NAME} STATIC
    src/driver.c
    src/rp2040.c
    src/mcp2515.c
)

target_compile_features(${MOD_NAME} PRIVATE cxx_std_11)

target_include_directories(${MOD_NAME}
    PRIVATE
    include
    ${APP_01_COMMON_INCLUDE_DIRECTORY}
)

target_link_libraries(${MOD_NAME}
    # PICO_SDK
    PRIVATE pico_stdlib
    PRIVATE hardware_spi
)