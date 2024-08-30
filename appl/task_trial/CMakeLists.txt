cmake_minimum_required(VERSION 3.14)

# Set appl name
set(APPL_NAME "Task_trial")

# Set appl version
set(APPL_VERSION "1.0.0")

# Set the appl root directory
if(DEFINED APPL_TASK_TRIAL_ROOT_DIRECTORY)
    set(APPL_ROOT_DIRECTORY ${APPL_TASK_TRIAL_ROOT_DIRECTORY})
else()
    set(APPL_ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# Set common include directory
set(APPL_INCLUDE_DIRECTORY "${APPL_ROOT_DIRECTORY}/include")

# Make project data accessible to compiler
add_compile_definitions(APP_NAME="${APPL_NAME}")
add_compile_definitions(APP_VERSION="${APPL_VERSION}")

# Include the sub modules
add_subdirectory( ${APPL_ROOT_DIRECTORY}/module/board_driver )

# Include appl source code file(s)
add_executable(${APPL_NAME}
    ${APPL_ROOT_DIRECTORY}/main.c
)

# Link to built libraries
target_link_libraries(${APPL_NAME}
    # RP2040
    PRIVATE pico_stdlib
    PRIVATE hardware_spi
    # FreeRTOS
    PRIVATE FreeRTOS
    # Appl
    PRIVATE board_driver_for_appl_trial_of_task
)

target_include_directories(${APPL_NAME}
    PRIVATE ${APPL_INCLUDE_DIRECTORY}
)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${APPL_NAME} TRUE)
pico_enable_stdio_uart(${APPL_NAME} TRUE)

# Enable extra build products
pico_add_extra_outputs(${APPL_NAME})
