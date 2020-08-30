add_subdirectory(library)

add_executable(lindengen main.c)
target_link_libraries(lindengen lindengenlib)