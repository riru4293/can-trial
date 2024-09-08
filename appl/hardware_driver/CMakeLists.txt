cmake_minimum_required(VERSION 3.13)

project( hardware_driver
    VERSION 1.0.0
    DESCRIPTION "Hardware driver"
    LANGUAGES CXX C ASM
)

# Add hardware_driver as a library
add_library(hardware_driver STATIC
  hardware_driver.c
  rp2040.c
  mcp2515.c
)

# Add the standard library to the build
target_link_libraries(hardware_driver
  # RP2040
  PRIVATE pico_stdlib
  PRIVATE hardware_spi
)

# Add the standard include files to the build
target_include_directories(hardware_driver
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
  PRIVATE
    ${APPL_INCLUDE_DIR}
)

pico_add_extra_outputs(hardware_driver)
