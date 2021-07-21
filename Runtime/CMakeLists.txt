cmake_minimum_required(VERSION 3.16)
project(AMPLE-Runtime VERSION "0.2.1")


set(CMAKE_C_STANDARD 99)


if (CMAKE_TOOLCHAIN_FILE)
find_package(CURL CONFIG REQUIRED)
add_definitions(-D__WITH_INSTALL__)
endif()


configure_file(include/stdAMPLE.h.in include/stdAMPLE.h @ONLY NEWLINE_STYLE CRLF)


include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

include_directories(${CURL_INCLUDE_DIRS})


file(GLOB SRC src/*.c src/*/*.c src/*/*/*.c)


add_executable(${PROJECT_NAME} ${SRC})


target_link_libraries(${PROJECT_NAME} AMPLE-Lib)
target_link_libraries(${PROJECT_NAME} AMPLE-IO-Lib)
target_link_libraries(${PROJECT_NAME} AMPLE-Utils-Lib)

target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})


install(TARGETS ${PROJECT_NAME} DESTINATION bin)