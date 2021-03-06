# {{PROJECT_NAME}}
{{DESCRIPTION}}

## Building
This project can be compiled using CMake:
1. Make a build directory and enter this directory.
2. Build the build files for your particular build environment.

For Linux, this comes down to:
1. `mkdir build && cd build`
2. `cmake ..`
3. `make`

### Testing
This project is tested using Check. To perform the the test, replace step 3 above with: `make test`.

Valgrind tests are also supported: `make valgrind_test_{{PROJECT_NAME}}`.

### Dependencies
For this project to compile, you will need:
- The SDL2 development library.
- The Check Unit Testing library.
