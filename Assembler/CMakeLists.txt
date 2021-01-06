cmake_minimum_required(VERSION 3.16)
project(AMPLE-Assembler VERSION "0.2.1")

set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB SRC src/*.c src/*/*.c src/*/*/*.c src/*/*/*/*.c)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} AMPLE-IO-Lib)
target_link_libraries(${PROJECT_NAME} AMPLE-Utils-Lib)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)