file(GLOB_RECURSE PROJECT_SOURCES *.c)
add_library(text-adventurelib ${PROJECT_SOURCES})
target_include_directories(text-adventurelib PUBLIC includes)