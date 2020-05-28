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

include_directories(include)
include_directories(../Libraries/AMPLE/include)

file(GLOB SRC "src/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SRC})