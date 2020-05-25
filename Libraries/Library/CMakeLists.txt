cmake_minimum_required(VERSION 3.16)
project(Library)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(../Exceptions)

include_directories(include)
include_directories(../AMPLE/include)

add_library(${PROJECT_NAME} STATIC src/Library.cpp ../IO/include/FileMode.h)
add_library(AMPLE::Library ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} AMPLE::Exceptions ${CMAKE_DL_LIBS})