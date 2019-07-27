file(GLOB_RECURSE PROJECT_SOURCES *.c)
add_library({{PROJECT_NAME}}lib ${PROJECT_SOURCES})
target_include_directories({{PROJECT_NAME}}lib PUBLIC includes)