cmake_minimum_required(VERSION 3.14)

# Set module name
set(MOD_NAME "board_driver_for_appl_trial_of_task")

project(${MOD_NAME} VERSION 1.0.0
    DESCRIPTION "Board driver"
    LANGUAGES CXX C ASM
)

add_library(${MOD_NAME} STATIC
    bd_api.c
    bd_gpio.c
)

target_compile_features(${MOD_NAME} PRIVATE cxx_std_11)

target_include_directories(${MOD_NAME}
    PRIVATE ${APPL_INCLUDE_DIRECTORY}
)

target_link_libraries(${MOD_NAME}
    PRIVATE pico_stdlib
    PRIVATE hardware_spi
)