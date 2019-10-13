add_subdirectory(library)

add_executable(text-adventure main.c)
target_link_libraries(text-adventure text-adventurelib)