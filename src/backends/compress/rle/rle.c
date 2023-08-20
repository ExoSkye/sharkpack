#include <sharkpack/backends/compress.h>
#include <sharkpack/errors.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>

u64 sp_get_decompressed_size(u8* src, u64 len) {
    if (len < 8) {
        exit(COMPRESS_FAILED_TO_GET_SIZE);
    } else {
        return *(u64*)src;
    }
}

void sp_decompress(u8* src, u64 len, u8* buffer) {
    // Skip the decompressed length section
    u8* current_compressed = (u8*)src + 8;

    u8* current_uncompressed = buffer;

    while (current_compressed < src + len) {
        // Check attributes
        bool is_copy = (*current_compressed & 0b10000000) > 0;
        bool next_byte_used = ((*current_compressed ^ 0b01111111) & 0b01111111) == 0;

        // Get the lengths (taking into considering whether it's a copy or not, or whether it's multibyte)
        u64 uncompressed_length = next_byte_used ? (*current_compressed & 0b01111111) + (*(current_compressed + 1)) : *current_compressed & 0b01111111;
        u64 compressed_length = is_copy ? 1 + (next_byte_used ? 2 : 1) : uncompressed_length + (next_byte_used ? 2 : 1);

        // Decompress!!
        for (u64 i = 0; i < uncompressed_length; i++) {
            *(current_uncompressed + i) = is_copy ? *(current_compressed + (next_byte_used ? 2 : 1)) : *(current_compressed + i + (next_byte_used ? 2 : 1));
        }

        // ADVANCE THE POINTERS!!!
        current_compressed += compressed_length;
        current_uncompressed += uncompressed_length;
    }
}

u8* sp_compress(u8* src, u64 len, u64* out_len) {
    u8* current = src;

    // allocate some memory, should be big enough??? (will be shortened after the fact)
    u8* output = (u8*)malloc(len * 2);
    u8* current_output = output;

    u8 byte;
    while (current < src + len) {
        byte = *current;
        current++;
        u8 current_byte = *current;

        if (byte == current_byte) {
            u16 length = 1;
            do {
                ++current;

                length++;
                if (current >= src + len) break;

                current_byte = *current;
            } while(byte == current_byte && length < 382 && current < src + len);

            if (length >= 127) {
                *current_output++ = 0b10000000 | 127;
                *current_output++ = length - 127;
            } else {
                *current_output++ = 0b10000000 | length;
            }

            *current_output++ = byte;
        } else {
            u8* current_start = current;
            u8 saved_byte = byte;
            u16 length = 0;
            do {
                byte = current_byte;
                ++current;

                length++;
                if (current >= src + len) break;

                current_byte = *current;
            } while(byte != current_byte && length < 382 && current < src + len);

            if (length >= 127) {
                *current_output++ = 127;
                *current_output++ = length - 127;
            } else {
                *current_output++ = length;
            }

            current = current_start;
            *current_output++ = saved_byte;

            for (u16 i = 0; i < length - 1; i++) {
                *current_output++ = *current++;
            }
        }
    }

    u64 compressed_len = (u64)current_output - (u64)output;

    u8* real_output = (u8*)calloc(8 + compressed_len, 1);
    memcpy(real_output + 8, output, compressed_len);
    *(u64*)real_output = len;

    free(output);
    *out_len = compressed_len + 8;

    return real_output;
}