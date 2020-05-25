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

add_subdirectory(Libraries/Library)
add_subdirectory(Libraries/Exceptions)
add_subdirectory(Libraries/IO)
add_subdirectory(Libraries/Memory)

include_directories(include)
include_directories(Libraries/AMPLE/include)

add_executable(${PROJECT_NAME} src/main.cpp src/Program.cpp src/Metadata.cpp Libraries/IO/src/File.cpp Libraries/IO/include/File.h)
target_link_libraries(${PROJECT_NAME} AMPLE::Library)
target_link_libraries(${PROJECT_NAME} AMPLE::Exceptions)
target_link_libraries(${PROJECT_NAME} AMPLE::IO)
target_link_libraries(${PROJECT_NAME} AMPLE::Memory)

#find_package(ICU 61.0 COMPONENTS uc i18n REQUIRED)
#target_link_libraries(AMPLE ICU::uc ICU::i18n)