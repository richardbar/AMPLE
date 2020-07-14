cmake_minimum_required(VERSION 3.16)
project(Core)

set(CMAKE_CXX_STANDARD 17)

get_filename_component(PARENT_DIR .. ABSOLUTE)

include_directories(include)
include_directories(${PARENT_DIR}/Libraries/AMPLE/include)

add_library(${PROJECT_NAME} SHARED src/astdio.cpp)

target_link_libraries(${PROJECT_NAME} Memory)