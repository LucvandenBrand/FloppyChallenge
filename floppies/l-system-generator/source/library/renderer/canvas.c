#include "renderer/canvas.h"
#include "memory/safe_alloc.h"

Canvas alloc_canvas(size_t width, size_t height)
{
    Canvas canvas;
    canvas.pixels = safe_malloc(sizeof(Colour) * width * height);
    canvas.width = width;
    canvas.height = height;
    return canvas;
}

void free_canvas(Canvas * canvas)
{
    free(canvas->pixels);
    canvas->pixels = NULL;
    canvas->width = 0;
    canvas->height = 0;
}

void clear_canvas(Canvas * canvas, Colour colour)
{
    for (size_t row = 0; row < canvas->height; row++)
        for (size_t col = 0; col < canvas->width; col++)
            set_pixel(canvas, colour, row, col);
}

void set_pixel(Canvas * canvas, Colour colour, size_t row, size_t col)
{
    // If outside bounds, ignore the draw.
    if (row < 0 || row >= canvas->height || col < 0 || col >= canvas->width)
        return;
    // Find the position in the 1D array and set the value.
    size_t index = row * canvas->width + col;
    canvas->pixels[index] = colour;
}

Colour get_pixel(Canvas canvas, size_t row, size_t col)
{
    // If outside bounds, return black
    Colour colour = create_colour_greyscale(0);
    if (row < 0 || row >= canvas.height || col < 0 || col >= canvas.width)
        return colour;

    // Find the position in the 1D array and return the value
    size_t index = row * canvas.width + col;
    return canvas.pixels[index];
}