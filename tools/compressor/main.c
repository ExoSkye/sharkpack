#include <sharkpack/sharkpack.h>
#include <malloc.h>
#include <memory.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("%s: <input file> <output file>\n", argv[0]);
        return 3;
    }

    FILE* in = fopen(argv[1], "rb");

    fseek(in, 0, SEEK_END);
    u64 in_len = ftell(in);
    fseek(in, 0, SEEK_SET);

    u8* input = (u8*)malloc(in_len);
    fread(input, 1, in_len, in);

    fclose(in);

    u64 out_length = 0;
    u8* output = sp_compress(input, in_len, &out_length);

    FILE* out = fopen(argv[2], "wb");

    fwrite(output, 1, out_length, out);

    fclose(out);

    u8* decompressed = sp_alloc_and_decompress(output, out_length);

    for (u64 i = 0; i < in_len; i++) {
        if (decompressed[i] != input[i]) {
            printf("Mismatch at %lx, please report", i);
        }
    }

    free(input);
    free(output);
    free(decompressed);

    return 0;
}
