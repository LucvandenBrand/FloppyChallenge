#include <limits.h>
#include "renderer/colour.h"
#include "math/bounds.h"

Colour create_colour_greyscale(float value)
{
    return create_colour(value, value, value);
}

Colour create_colour(float red, float green, float blue)
{
    red = clamp(red, 0, 1);
    green = clamp(green, 0, 1);
    blue = clamp(blue, 0, 1);
    Colour colour;
    colour.red = (char) (red * (float) UCHAR_MAX);
    colour.green = (char) (green * (float) UCHAR_MAX);
    colour.blue = (char) (blue * (float) UCHAR_MAX);
    return colour;
}

void colour_to_png_byte(png_byte * byte, Colour colour)
{
    byte[0] = colour.red;
    byte[1] = colour.green;
    byte[2] = colour.blue;
}