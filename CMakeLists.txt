cmake_minimum_required(VERSION 3.26)
project(sharkpack C)

set(CMAKE_C_STANDARD 11)

include(asan.cmake)
include(src/backends/backends.cmake)

