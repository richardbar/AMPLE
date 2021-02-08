cmake_minimum_required(VERSION 3.16)
project(AMPLE-Utils-Lib VERSION "0.2.1")

set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB SRC src/*.c)

add_library(${PROJECT_NAME} STATIC ${SRC} ${HEADERS})
target_link_libraries(${PROJECT_NAME} AMPLE-IO-Lib)
target_link_libraries(${PROJECT_NAME} AMPLE-Lib)

target_include_directories(${PROJECT_NAME} PUBLIC include)
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)