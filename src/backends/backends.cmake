set(COMPRESSION_BACKEND "None" CACHE STRING "Compression backend to use")
set(MM_BACKEND "None" CACHE STRING "Compression backend to use")

set(SHARKPACK_COMPRESSION_BACKEND_PATHS)
set(SHARKPACK_COMPRESSION_BACKEND_NAMES)
set(SHARKPACK_MM_BACKEND_PATHS)
set(SHARKPACK_MM_BACKEND_NAMES)

macro(register_backend name path type)
    string(TOUPPER ${type} upper_type)
    list(APPEND SHARKPACK_${upper_type}_BACKEND_PATHS ${path})
    list(APPEND SHARKPACK_${upper_type}_BACKEND_NAMES ${name})

    message(STATUS "Successfully registered ${type} backend `${name}`")
endmacro()

file(GLOB_RECURSE backend_files CONFIGURE_DEPENDS "*.backend.cmake")

foreach(backend_file ${backend_files})
    include(${backend_file})
endforeach()

if (COMPRESSION_BACKEND STREQUAL "None")
    message(FATAL_ERROR "Please specify a compression backend")
endif()

if (MM_BACKEND STREQUAL "None")
    message(FATAL_ERROR "Please specify a mm backend")
endif()

list(FIND SHARKPACK_COMPRESSION_BACKEND_NAMES ${COMPRESSION_BACKEND} compression_backend_idx)
list(FIND SHARKPACK_MM_BACKEND_NAMES ${MM_BACKEND} mm_backend_idx)

if (compression_backend_idx EQUAL -1)
    message(FATAL_ERROR "Please specify a valid compression backend (${COMPRESSION_BACKEND} does not exist)")
endif()

if (mm_backend_idx EQUAL -1)
    message(FATAL_ERROR "Please specify a valid mm backend (${COMPRESSION_BACKEND} does not exist)")
endif()

list(GET SHARKPACK_COMPRESSION_BACKEND_PATHS ${compression_backend_idx} compression_backend_path)
list(GET SHARKPACK_MM_BACKEND_PATHS ${mm_backend_idx} mm_backend_path)

cmake_path(REPLACE_EXTENSION compression_backend_path ".check.cmake" OUTPUT_VARIABLE compression_backend_check_path)

include(${compression_backend_check_path})

if (NOT DEFINED SHARKPACK_COMPRESSION_WORKS)
    message(FATAL_ERROR "Please specify a compression backend that works on your system")
endif()

cmake_path(REPLACE_EXTENSION mm_backend_path ".check.cmake" OUTPUT_VARIABLE mm_backend_check_path)

include(${mm_backend_check_path})

if (NOT DEFINED SHARKPACK_MM_WORKS)
    message(FATAL_ERROR "Please specify a mm backend that works on your system")
endif()

list(GET SHARKPACK_COMPRESSION_BACKEND_NAMES ${compression_backend_idx} compression_backend_name)
set(COMPRESSION_BACKEND_LIB sharkpack_${compression_backend_name}_compression)

list(GET SHARKPACK_MM_BACKEND_NAMES ${mm_backend_idx} mm_backend_name)
set(MM_BACKEND_LIB sharkpack_${compression_mm_name}_mm)