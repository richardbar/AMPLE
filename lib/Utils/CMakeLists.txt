cmake_minimum_required(VERSION 3.16)
project(AMPLE-Utils-Lib VERSION "0.0.1")

set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB SRC src/*.c)

add_library(${PROJECT_NAME} SHARED ${SRC} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include)