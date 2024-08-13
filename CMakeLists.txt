cmake_minimum_required(VERSION 3.14)

# Set project data
set(PROJECT_NAME "CAN-TRIAL_PROJECT")

# Set app name(s) and version(s)
set(APP_01_NAME "appl_01")
set(APP_01_VERSION_NUMBER "0.0.2")

set(APP_09_NAME "appl_09")
set(APP_09_VERSION_NUMBER "0.0.1")

# Specify the app(s) source code
set(APP_01_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/appl_01")
set(APP_09_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/appl_09")

# FROM 1.4.2 -- Set app-side debugging on debug builds
# Now uses CMake generator expression to extract config type
add_compile_definitions($<$<CONFIG:Debug>:DEBUG=1>)

# Set env variable 'PICO_SDK_PATH' to the local Pico SDK
# Comment out the set() if you have a global copy of the
# SDK set and $PICO_SDK_PATH defined in your $PATH
set(ENV{PICO_SDK_PATH} "${CMAKE_SOURCE_DIR}/pico-sdk")

# Set flags and directory variables
set(FREERTOS_CFG_DIRECTORY "${CMAKE_SOURCE_DIR}/FreeRTOS-Config")
set(FREERTOS_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel")
set(APP_01_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/${APP_01_NAME}/include")
set(APP_09_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/${APP_09_NAME}/include")

# Include the Pico SDK
include(pico_sdk_import.cmake)

# Name the project
project(${PROJECT_NAME}
        LANGUAGES C CXX ASM
        DESCRIPTION "FreeRTOS-based RP2040 applications"
)

# Initialise the Pico SDK
pico_sdk_init()


# Add FreeRTOS as a library
add_library(FreeRTOS STATIC
    ${FREERTOS_SRC_DIRECTORY}/event_groups.c
    ${FREERTOS_SRC_DIRECTORY}/list.c
    ${FREERTOS_SRC_DIRECTORY}/queue.c
    ${FREERTOS_SRC_DIRECTORY}/stream_buffer.c
    ${FREERTOS_SRC_DIRECTORY}/tasks.c
    ${FREERTOS_SRC_DIRECTORY}/timers.c
    ${FREERTOS_SRC_DIRECTORY}/portable/MemMang/heap_3.c
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0/port.c
)

# Build FreeRTOS
target_include_directories(FreeRTOS PUBLIC
    ${FREERTOS_CFG_DIRECTORY}/
    ${FREERTOS_SRC_DIRECTORY}/include
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0
)

# Include the apps' source code
add_subdirectory(${APP_01_SRC_DIRECTORY})
add_subdirectory(${APP_09_SRC_DIRECTORY})
