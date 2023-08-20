#include <sharkpack/backends/compress.h>
#include <malloc.h>

// Blanket definitions

u8* sp_alloc_and_decompress(u8* src, u64 len) {
    u8* output = (u8*)malloc(sp_get_decompressed_size(src, len));
    sp_decompress(src, len, output);
    return output;
}