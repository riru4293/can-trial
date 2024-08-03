cmake_minimum_required( VERSION 3.12 )

project(
    spi_wrapper
    VERSION 1.0.0
    DESCRIPTION "SPI communication wrapper"
    LANGUAGES CXX C ASM
)

add_library(
    spi_wrapper         #[[name]]
    STATIC              #[[type: STATIC,SHARED,MODULE]]
    src/spi_wrapper.c   #[[source files]]
)

target_compile_features(
    spi_wrapper
    PRIVATE
    cxx_std_11
)

target_include_directories(
    spi_wrapper
    PUBLIC include
)

target_link_libraries(
    spi_wrapper
    PUBLIC app_comdef
    PRIVATE pico_stdlib
    PRIVATE hardware_spi
)
