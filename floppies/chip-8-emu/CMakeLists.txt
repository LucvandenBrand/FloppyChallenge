cmake_minimum_required(VERSION 3.9)
project(chip-8-emu)

# Custom cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Make libraries statically linked
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(source)

enable_testing()

add_subdirectory(tests)