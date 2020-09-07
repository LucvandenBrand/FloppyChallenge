#ifndef COLOUR_H
#define COLOUR_H

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Colour;

Colour create_colour_greyscale(float value);
Colour create_colour(float red, float green, float blue);

#endif