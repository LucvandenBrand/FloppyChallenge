cmake_minimum_required(VERSION 3.9)
project({{PROJECT_NAME}})

# Add app sources
file(GLOB_RECURSE PROJECT_SOURCES source/*.c source/*.h)
add_executable({{PROJECT_NAME}} ${PROJECT_SOURCES})

# Compilation settings
set_property(TARGET {{PROJECT_NAME}} PROPERTY C_STANDARD 99)

