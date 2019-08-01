add_subdirectory(library)

add_executable(chip-8-emu main.c)
target_link_libraries(chip-8-emu chip-8-emulib)