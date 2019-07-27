add_subdirectory(library)

add_executable({{PROJECT_NAME}} main.c)
target_link_libraries({{PROJECT_NAME}} {{PROJECT_NAME}}lib)