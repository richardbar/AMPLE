cmake_minimum_required(VERSION 3.16)
project(AMPLE)

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

file(GLOB SRC "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} Library)
target_link_libraries(${PROJECT_NAME} Exceptions)
target_link_libraries(${PROJECT_NAME} IO)
target_link_libraries(${PROJECT_NAME} Memory)

#find_package(ICU 61.0 COMPONENTS uc i18n REQUIRED)
#target_link_libraries(AMPLE ICU::uc ICU::i18n)
