cmake_minimum_required(VERSION 3.16)
project(AMPLE-OPCODE-V2 VERSION "2")

set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB SRC src/*.c src/*/*.c)

add_library(${PROJECT_NAME} SHARED ${SRC})

target_link_libraries(${PROJECT_NAME} AMPLE-Lib)
target_link_libraries(${PROJECT_NAME} AMPLE-IO-Lib)
target_link_libraries(${PROJECT_NAME} AMPLE-Utils-Lib)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION Versions)