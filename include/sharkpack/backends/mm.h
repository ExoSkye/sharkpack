#ifndef SHARKPACK_MM_H
#define SHARKPACK_MM_H

#include <sharkpack/typedefs.h>

/**
 * Allocates memory that can be set as executable in the future (ie on Linux this allocates properly aligned memory)
 * @param size the amount of memory to allocate in bytes
 * @returns a pointer to the memory that was allocated
 */
u8* sp_allocate_executable_memory(u64 size);

/**
 * Sets the memory at addr as executable, (RX)
 * @param addr the memory to be set as executable
 * @param size the amount of memory allocated at addr
 * @returns the pointer to the now executable memory
 */
u8* sp_set_memory_as_executable(u8* addr, u64 size);

/**
 * Sets the memory at addr as executable, (RW)
 * @param addr the memory to be set as executable
 * @param size the amount of memory allocated at addr
 * @returns the pointer to the now executable memory
 */
u8* sp_set_memory_as_writable(u8* addr, u64 size);

#endif //SHARKPACK_MM_H
