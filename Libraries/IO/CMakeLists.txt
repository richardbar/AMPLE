cmake_minimum_required(VERSION 3.16)
project(IO)

set(CMAKE_CXX_STANDARD 17)

get_filename_component(PARENT_DIR ../ ABSOLUTE)

include_directories(include)
include_directories(../AMPLE/include)

file(GLOB SRC "src/*.cpp")
file(GLOB HEADERS "include/*.h")

find_library(${PROJECT_NAME}_LIB ${PROJECT_NAME})
if (NOT ${PROJECT_NAME}_LIB)
    add_library(${PROJECT_NAME} STATIC ${SRC} ${HEADERS})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} Exceptions ${CMAKE_DL_LIBS})