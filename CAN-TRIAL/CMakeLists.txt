cmake_minimum_required(VERSION 3.14)

# Make project data accessible to compiler
add_compile_definitions(APP_NAME="${APP_NAME}")
add_compile_definitions(APP_VERSION="${APP_VERSION_NUMBER}")
add_compile_definitions(BUILD_NUM=${BUILD_NUMBER})


add_subdirectory( module/board_driver )


# Include app source code file(s)
add_executable(${APP_NAME}
    ${APP_SRC_DIRECTORY}/main.c
)

# Link to built libraries
target_link_libraries(${APP_NAME}
    PRIVATE pico_stdlib
    PRIVATE FreeRTOS
    PRIVATE board_driver
    # can_driver
    # spi_wrapper
)

target_include_directories(${APP_NAME}
    PRIVATE
    include
    module
)

# Enable/disable STDIO via USB and UART
pico_enable_stdio_usb(${APP_NAME} TRUE)
pico_enable_stdio_uart(${APP_NAME} TRUE)

# Enable extra build products
pico_add_extra_outputs(${APP_NAME})
