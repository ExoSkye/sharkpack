register_backend(linux mm)

add_library(sharkpack_linux_mm STATIC src/backends/mm/linux/linux.c)
target_include_directories(sharkpack_linux_mm PUBLIC include)
turn_on_lto(sharkpack_linux_mm)