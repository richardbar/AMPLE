cmake_minimum_required(VERSION 3.16)
project(AMPLE-Assembler VERSION "0.1.1")

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SRC src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} AMPLE-IO-Lib)
target_link_libraries(${PROJECT_NAME} AMPLE-Utils-Lib)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)