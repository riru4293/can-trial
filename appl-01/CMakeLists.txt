cmake_minimum_required(VERSION 3.14)

# Make project data accessible to compiler
add_compile_definitions(APP_NAME="${APP_01_NAME}")
add_compile_definitions(APP_VERSION="${APP_01_VERSION_NUMBER}")


add_subdirectory( module/board_driver )


# Include app source code file(s)
add_executable(${APP_01_NAME}
    ${APP_01_SRC_DIRECTORY}/main.c
    ${APP_01_SRC_DIRECTORY}/temp.c
)

# Link to built libraries
target_link_libraries(${APP_01_NAME}
    PRIVATE pico_stdlib
    PRIVATE FreeRTOS
    PRIVATE board_driver
    # can_driver
    # spi_wrapper
    PRIVATE hardware_spi
)

target_include_directories(${APP_01_NAME}
    PRIVATE
    include
    module
)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${APP_01_NAME} TRUE)
pico_enable_stdio_uart(${APP_01_NAME} TRUE)

# Enable extra build products
pico_add_extra_outputs(${APP_01_NAME})
