cmake_minimum_required(VERSION 3.16)
project(Core)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
get_filename_component(PARENT_DIR .. ABSOLUTE)

add_subdirectory(${PARENT_DIR}/Libraries/Exceptions Exceptions)
add_subdirectory(${PARENT_DIR}/Libraries/Library Library)
add_subdirectory(${PARENT_DIR}/Libraries/IO IO)
add_subdirectory(${PARENT_DIR}/Libraries/Memory Memory)

include_directories(include)
include_directories(${PARENT_DIR}/Libraries/AMPLE/include)

add_library(${PROJECT_NAME} SHARED src/astdio.cpp)

target_link_libraries(${PROJECT_NAME} Memory)