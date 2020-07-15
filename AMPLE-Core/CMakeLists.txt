cmake_minimum_required(VERSION 3.16)
project(Core)

set(CMAKE_CXX_STANDARD 17)

get_filename_component(PARENT_DIR .. ABSOLUTE)

include_directories(include)
include_directories(${PARENT_DIR}/Libraries/AMPLE/include)

file(GLOB SRC "src/*.cpp" "src/*.c")

add_library(${PROJECT_NAME} SHARED ${SRC})

target_link_libraries(${PROJECT_NAME} Memory)