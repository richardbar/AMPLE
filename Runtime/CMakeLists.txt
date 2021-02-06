cmake_minimum_required(VERSION 3.16)
project(AMPLE-Runtime VERSION "0.2.1")

set(CMAKE_C_STANDARD 99)

configure_file(include/stdAMPLE.h.in include/stdAMPLE.h @ONLY NEWLINE_STYLE CRLF)

include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

file(GLOB SRC src/*.c src/*/*/*.c src/*/*/OP_CODES/*.c)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} AMPLE-Lib)
target_link_libraries(${PROJECT_NAME} AMPLE-IO-Lib)
target_link_libraries(${PROJECT_NAME} AMPLE-Utils-Lib)
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})

add_dependencies(${PROJECT_NAME} AMPLE-OPCODE-V1)
add_dependencies(${PROJECT_NAME} AMPLE-OPCODE-V2)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)