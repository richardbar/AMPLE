cmake_minimum_required(VERSION 3.16)
project(Exceptions)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(${PROJECT_NAME} STATIC src/DllNotFoundException.cpp src/MissingMethodException.cpp src/IndexOutOfRangeException.cpp)
add_library(AMPLE::Exceptions ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)