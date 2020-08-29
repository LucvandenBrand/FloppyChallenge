add_subdirectory(library)

add_executable(L-system generator main.c)
target_link_libraries(L-system generator L-system generatorlib)