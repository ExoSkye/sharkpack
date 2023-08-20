cmake_minimum_required(VERSION 3.26)
project(sharkpack C)

set(CMAKE_C_STANDARD 11)

include(additional-profiles.cmake)
include(src/backends/backends.cmake)

add_executable(sharkpack_compressor tools/compressor/main.c)
target_link_libraries(sharkpack_compressor PUBLIC ${COMPRESSION_BACKEND_LIB})