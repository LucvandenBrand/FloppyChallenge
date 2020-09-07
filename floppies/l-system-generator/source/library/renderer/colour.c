#include <limits.h>
#include "renderer/colour.h"

Colour create_colour_greyscale(float value)
{
    return create_colour(value, value, value);
}

float clamp(float value, float min_value, float max_value) {
    const float clamp_min = value < min_value ? min_value : value;
    return clamp_min > max_value ? max_value : value;
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