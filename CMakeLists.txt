cmake_minimum_required(VERSION 3.16)

# Universal ESP32 UART UTF-8 Console Component
idf_component_register(
    SRCS
        "src/uart_utf8_console.c"
    INCLUDE_DIRS
        "include"
    PRIV_REQUIRES
        driver
        esp_driver_uart
        freertos
        vfs
)

