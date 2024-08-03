cmake_minimum_required( VERSION 3.12 )

project(
    app_comdef
    VERSION 1.0.0
    DESCRIPTION "A header-only c library. Provides a common definitions for application."
    LANGUAGES CXX C ASM
)

add_library(
    app_comdef          #[[name]]
    INTERFACE           #[[type]]
)

target_include_directories(
    app_comdef
    INTERFACE include
)
