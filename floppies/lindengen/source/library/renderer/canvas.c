#include <png.h>
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

bool save_canvas_as_png(Canvas canvas, const char * file_path)
{
    // Create file
    FILE * file_ptr = fopen(file_path, "wb");
    if (file_ptr == NULL)
    {
        printf("Could not create file.\n");
        return false;
    }

    // Create PNG data structs
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL)
        return false;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
        png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
        return false;
    }

    // Init PNG file
    png_init_io(png_ptr, file_ptr);
    png_set_IHDR(png_ptr, info_ptr, canvas.width, canvas.height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    // Set the title
    png_text title_text;
    title_text.compression = PNG_TEXT_COMPRESSION_NONE;
    title_text.key = "Title";
    title_text.text = "L-system";
    png_set_text(png_ptr, info_ptr, &title_text, 1);
    png_write_info(png_ptr, info_ptr);

    // Write image data
    png_bytep row = (png_bytep) safe_malloc(3 * canvas.width * sizeof(png_byte));
    for (size_t y = 0; y < canvas.height; y++)
    {
        for (size_t x = 0; x < canvas.width; x++)
        {
            Colour colour = get_pixel(canvas, y, x);
            colour_to_png_byte(&(row[x*3]), colour);
        }
        png_write_row(png_ptr, row);
    }

    png_write_end(png_ptr, NULL);
    fclose(file_ptr);
    png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
    free(row);

    return true;
}