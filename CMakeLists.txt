cmake_minimum_required(VERSION 3.16)
project(AMPLE)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Libraries/Library)
add_subdirectory(Libraries/Exceptions)
add_subdirectory(Libraries/Memory)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp src/Program.cpp src/Metadata.cpp)
target_link_libraries(${PROJECT_NAME} AMPLE::Library)
target_link_libraries(${PROJECT_NAME} AMPLE::Exceptions)
target_link_libraries(${PROJECT_NAME} AMPLE::Memory)

#find_package(ICU 61.0 COMPONENTS uc i18n REQUIRED)
#target_link_libraries(AMPLE ICU::uc ICU::i18n)