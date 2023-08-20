register_backend(rle ${CMAKE_CURRENT_LIST_FILE} compression)

add_library(sharkpack_rle_compression STATIC src/backends/compress/compress.c src/backends/compress/rle/rle.c)
target_include_directories(sharkpack_rle_compression PUBLIC include)