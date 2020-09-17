# Lindengen
Simple L-system generator.

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

Valgrind tests are also supported: `make valgrind_test_L-system generator`.

### Dependencies
For this project to compile, you will need:
- The libpng library. Install using apt: `sudo apt-get install libpng-dev`.
- The Check Unit Testing library.
