#include <sharkpack/backends/mm.h>
#include <sharkpack/errors.h>
#include <unistr.h>
#include <unistd.h>
#include <sys/mman.h>

u8* sp_allocate_executable_memory(u64 size) {
    u8* aligned_memory = NULL;
    posix_memalign((void **)&aligned_memory, getpagesize(), size);

    if (aligned_memory == NULL) {
        exit(MM_FAILED_TO_ALLOC);
    }
    // Ensure RW
    if(mprotect(aligned_memory, size, PROT_READ | PROT_WRITE) < 0) {
        exit(MM_FAILED_TO_SET_RW);
    }

    return aligned_memory;
}

u8* sp_set_memory_as_executable(u8* addr, u64 size) {
    if(mprotect(addr, size, PROT_READ | PROT_WRITE) < 0) {
        exit(MM_FAILED_TO_SET_RX);
    }

    return addr;
}

u8* sp_set_memory_as_writable(u8* addr, u64 size) {
    if(mprotect(addr, size, PROT_READ | PROT_WRITE) < 0) {
        exit(MM_FAILED_TO_SET_RW);
    }

    return addr;
}