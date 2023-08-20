cmake_minimum_required(VERSION 3.9.4)
project(sharkpack C)

set(CMAKE_C_STANDARD 11)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-Os)
endif()

include(utils.cmake)
include(additional-profiles.cmake)
include(src/backends/backends.cmake)

add_executable(sharkpack_compressor tools/compressor/main.c)
target_link_libraries(sharkpack_compressor PUBLIC ${COMPRESSION_BACKEND_LIB})
turn_on_lto(sharkpack_compressor)