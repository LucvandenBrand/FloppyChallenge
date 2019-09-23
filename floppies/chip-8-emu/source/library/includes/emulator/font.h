#ifndef FONT_H
#define FONT_H

#include <stdint.h>
#define CHAR_SIZE 5
#define NUM_CHARS 16
#define FONT_SIZE CHAR_SIZE*NUM_CHARS
void load_chip8_font(uint8_t * memory);

#endif