cmake_minimum_required(VERSION 3.16)
project(AMPLE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC" )
endif()

add_subdirectory(lib)
add_subdirectory(Versions)
add_subdirectory(Assembler)
add_subdirectory(Runtime)

