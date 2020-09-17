#ifndef COLOUR_H
#define COLOUR_H

#include <png.h>

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Colour;

Colour create_colour_greyscale(float value);
Colour create_colour(float red, float green, float blue);
void colour_to_png_byte(png_byte * byte, Colour colour);

#endif