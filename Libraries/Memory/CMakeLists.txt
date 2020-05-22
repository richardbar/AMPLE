cmake_minimum_required(VERSION 3.16)
project(Memory)

set(CMAKE_CXX_STANDARD 17)

include_directories(../Exceptions)
include_directories(../Library)

include_directories(include)

add_library(${PROJECT_NAME} STATIC src/Memory.cpp)
add_library(AMPLE::Memory ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} AMPLE::Exceptions ${CMAKE_DL_LIBS})
target_link_libraries(${PROJECT_NAME} AMPLE::Library ${CMAKE_DL_LIBS})