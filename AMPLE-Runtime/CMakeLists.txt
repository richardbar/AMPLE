cmake_minimum_required(VERSION 3.16)
project(AMPLE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

get_filename_component(PARENT_DIR .. ABSOLUTE)

include_directories(include include/*)
include_directories(${PARENT_DIR}/Libraries/AMPLE/include)

file(GLOB SRC "src/*.cpp" "src/*.c" "src/opcodes/*.c" "src/opcodes/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} Library)
target_link_libraries(${PROJECT_NAME} Exceptions)
target_link_libraries(${PROJECT_NAME} IO)
target_link_libraries(${PROJECT_NAME} Memory)