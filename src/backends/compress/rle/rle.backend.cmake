register_backend(rle compression)

add_library(sharkpack_rle_compression STATIC src/backends/compress/compress.c src/backends/compress/rle/rle.c)
target_include_directories(sharkpack_rle_compression PUBLIC include)
turn_on_lto(sharkpack_rle_compression)