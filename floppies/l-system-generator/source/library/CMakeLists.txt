file(GLOB_RECURSE PROJECT_SOURCES *.c)
add_library(L-system generatorlib ${PROJECT_SOURCES})
target_include_directories(L-system generatorlib PUBLIC includes)