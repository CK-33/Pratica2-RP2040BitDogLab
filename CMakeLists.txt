cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(P2RP2040 C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# Gera o header a partir do arquivo PIO
pico_generate_pio_header(P2RP2040 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

add_executable(P2RP2040
    P2RP2040.c
)

target_link_libraries(P2RP2040
    pico_stdlib
    hardware_pio
    hardware_clocks
)

pico_add_extra_outputs(P2RP2040)

pico_enable_stdio_usb(P2RP2040 1)
pico_enable_stdio_uart(P2RP2040 0)
