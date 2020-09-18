#ifndef CANVAS_H
#define CANVAS_H

#include <stdbool.h>
#include <stdio.h>
#include "renderer/colour.h"

typedef struct
{
    Colour * pixels;
    size_t width;
    size_t height;
} Canvas;

Canvas alloc_canvas(size_t width, size_t height);
void free_canvas(Canvas * canvas);
void clear_canvas(Canvas * canvas, Colour colour);
void set_pixel(Canvas * canvas, Colour colour, size_t row, size_t col);
Colour get_pixel(Canvas canvas, size_t row, size_t col);
bool save_canvas_as_png(Canvas canvas, const char * file_path);

#endif