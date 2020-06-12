# text-adventure
Short text adventure to play on your terminal.

## Building
This project can be compiled using CMake:
1. Make a build directory and enter this directory.
2. Build the build files for your particular build environment.

For Linux, this comes down to:
1. `mkdir build && cd build`
2. `cmake ..`
3. `make`

## Editing
The actual story can be edited through direct manipulation of the `data\game_data.json` file, but be sure to have a backup!
The recommended (and more fun) method is to use the **story editor** in the `editor` folder.
Open the `index.html` file with your web browser.

### Testing
This project is tested using Check. To perform the the test, replace step 3 above with: `make test`.

Valgrind tests are also supported: `make valgrind_test_text-adventure`.

### Dependencies
For this project to compile, you will need:
- The SDL2 development library.
- The Check Unit Testing library.
