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

add_executable(${PROJECT_NAME} src/main.cpp src/Program.cpp src/Metadata.cpp)
target_link_libraries(${PROJECT_NAME} AMPLE::Library)
target_link_libraries(${PROJECT_NAME} AMPLE::Exceptions)
target_link_libraries(${PROJECT_NAME} AMPLE::IO)
target_link_libraries(${PROJECT_NAME} AMPLE::Memory)

#find_package(ICU 61.0 COMPONENTS uc i18n REQUIRED)
#target_link_libraries(AMPLE ICU::uc ICU::i18n)
