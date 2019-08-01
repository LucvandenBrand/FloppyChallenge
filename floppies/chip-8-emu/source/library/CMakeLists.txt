file(GLOB_RECURSE PROJECT_SOURCES *.c)
add_library(chip-8-emulib ${PROJECT_SOURCES})
target_include_directories(chip-8-emulib PUBLIC includes)