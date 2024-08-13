cmake_minimum_required(VERSION 3.14)

# Make project data accessible to compiler
add_compile_definitions(APP_NAME="${APP_09_NAME}")
add_compile_definitions(APP_VERSION="${APP_09_VERSION_NUMBER}")


add_subdirectory( module/board_driver )


# Include app source code file(s)
add_executable(${APP_09_NAME}
    ${APP_09_SRC_DIRECTORY}/main.c
    ${APP_09_SRC_DIRECTORY}/temp.c
)

# Link to built libraries
target_link_libraries(${APP_09_NAME}
    PRIVATE pico_stdlib
    PRIVATE FreeRTOS
    PRIVATE board_driver_for_appl_09
    # can_driver
    # spi_wrapper
    PRIVATE hardware_spi
)

target_include_directories(${APP_09_NAME}
    PRIVATE
    include
    module
)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${APP_09_NAME} TRUE)
pico_enable_stdio_uart(${APP_09_NAME} TRUE)

# Enable extra build products
pico_add_extra_outputs(${APP_09_NAME})
