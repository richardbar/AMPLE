cmake_minimum_required(VERSION 3.16)
project(AMPLE-Assembler)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(${PARENT_DIR}/Libraries/AMPLE/include)

file(GLOB SRC "src/*.cpp" "src/*.c")

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} Library)
target_link_libraries(${PROJECT_NAME} Exceptions)
target_link_libraries(${PROJECT_NAME} IO)
target_link_libraries(${PROJECT_NAME} Memory)

#find_package(ICU 61.0 COMPONENTS uc i18n REQUIRED)
#target_link_libraries(AMPLE ICU::uc ICU::i18n)
