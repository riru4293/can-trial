cmake_minimum_required(VERSION 3.14)

# Set module name
set(MOD_NAME "board_driver")

project(${MOD_NAME} VERSION 1.0.0
    DESCRIPTION "Board driver"
    LANGUAGES CXX C ASM
)

add_library(${MOD_NAME} STATIC
    src/bd_api.c
    src/bd_gpio.c
)

target_compile_features(${MOD_NAME} PRIVATE cxx_std_11)

target_include_directories(${MOD_NAME}
    PRIVATE
    include
    ${COMMON_INCLUDE_DIRECTORY}
)

target_link_libraries(${MOD_NAME}
    PRIVATE pico_stdlib
    PRIVATE hardware_spi
)