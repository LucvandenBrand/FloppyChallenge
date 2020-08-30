file(GLOB_RECURSE PROJECT_SOURCES *.c)
add_library(lindengenlib ${PROJECT_SOURCES})
target_include_directories(lindengenlib PUBLIC includes)