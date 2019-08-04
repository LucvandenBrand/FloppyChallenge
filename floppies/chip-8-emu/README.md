# chip-8-emu
A tiny CHIP-8 emulator. The CHIP-8 is a computer which only exists in theory. 
It has been used as a virtual platform for developing cross-platform computer games. 
For more information, please visit its [wiki page](https://en.wikipedia.org/wiki/CHIP-8).

## Usage
Simply call the executable with the ROM file as its first positional parameter: 
`chip-8-emu path/to/rom/file`. A collection of public domain ROM files is stored in `test_roms`.

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

Valgrind tests are also supported: `make valgrind_test_chip-8-emu`.

### Dependencies
For this project to compile, you will need:
- The SDL2 development library.
- The Check Unit Testing library.
