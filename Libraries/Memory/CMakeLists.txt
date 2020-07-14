cmake_minimum_required(VERSION 3.16)
project(Memory)

set(CMAKE_C_STANDARD 99)

get_filename_component(PARENT_DIR .. ABSOLUTE)

include_directories(include)
include_directories(../AMPLE/include)

file(GLOB SRC "src/*.c")
file(GLOB HEADERS "include/*.h")
add_library(${PROJECT_NAME} STATIC ${SRC} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)