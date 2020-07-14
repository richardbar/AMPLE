cmake_minimum_required(VERSION 3.16)

add_subdirectory(Libraries/Exceptions Exceptions)
add_subdirectory(Libraries/Library Library)
add_subdirectory(Libraries/IO IO)
add_subdirectory(Libraries/Memory Memory)

add_subdirectory(AMPLE-Assembler)
add_subdirectory(AMPLE-Runtime)
add_subdirectory(AMPLE-Core)