#ifndef SHARKPACK_COMPRESS_H
#define SHARKPACK_COMPRESS_H

#include <sharkpack/typedefs.h>

/**
 * Get the decompressed size of the compressed data in src
 * @param src the data to get the decompressed size of
 * @param len the length of the data pointed to by src
 * @return the decompressed size of src
 */
u64 sp_get_decompressed_size(u8* src, u64 len);

/**
 * Decompress the data in src into buffer
 * @param src the data to decompress
 * @param len the length of the data to decompress
 * @param buffer the memory to write the decompressed memory to
 */
void sp_decompress(u8* src, u64 len, u8* buffer);

/**
 * Decompresses the compressed data in src into a newly allocated buffer
 * @param src the data to decompress
 * @param len the length of the data to decompress
 * @return the newly allocated buffer, now filled with decompressed data
 */
u8* sp_alloc_and_decompress(u8* src, u64 len);

/**
 * Compresses the data in src into a newly allocated buffer
 * @param src the data to compress
 * @param len the length of the data to compress
 * @param out_len pointer to a variable where the size of the compressed data is stored
 * @return the newly allocated buffer, filled with compressed data
 */
u8* sp_compress(u8* src, u64 len, u64* out_len);

#endif //SHARKPACK_COMPRESS_H
