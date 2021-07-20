# cmake -G "Unix Makefiles"

cmake_minimum_required(VERSION 3.20)

message("Building for: " ${CMAKE_GENERATOR})

set(CMAKE_C_COMPILER SDCC)
#set(CMAKE_C_FLAGS "--verbose -mmcs51 --opt-code-size --no-xinit-opt -D FOSC_160000")
set(CMAKE_C_FLAGS "-mmcs51 --opt-code-size -D FOSC_160000")
#set(CMAKE_CXX_COMPILER SDCC)
#set(CMAKE_C_STANDARD 99)
set(CMAKE_SYSTEM_NAME Generic)

set(PROJECT_NAME usb00)
project(${PROJECT_NAME} VERSION 0.0 LANGUAGES C)

include_directories(
    .
    ./Include
)

set(SOURCES
    main.c
    common.c
    uart.c
    tmr.c
    usbd12.c
    usbcore.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND packihx ${PROJECT_NAME}.ihx > ${PROJECT_NAME}.hex
    COMMAND makebin -p ${PROJECT_NAME}.hex ${PROJECT_NAME}.bin
)
