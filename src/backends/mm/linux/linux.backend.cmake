register_backend(linux ${CMAKE_CURRENT_LIST_FILE} mm)

add_library(sharkpack_linux_mm STATIC src/backends/mm/linux/linux.c)
target_include_directories(sharkpack_linux_mm PUBLIC include)