#include <math.h>
#include "math/point.h"
#include "math/generic.h"
#include "renderer/turtle.h"
#include "renderer/canvas.h"

void render_system_to_canvas(LSystem system, MoveMap move_map, Canvas * canvas)
{
    PointList polyline = alloc_empty_point_list();
    build_polyline_from_system(&polyline, move_map, system);
    render_polyline_to_canvas(polyline, canvas);
    free_point_list(&polyline);
}

void build_polyline_from_system(PointList * polyline, MoveMap move_map, LSystem system)
{
    Point turtle = {0, 0};
    float turtle_direction =  M_PI / 2;
    add_point_to_list(turtle, polyline);
    for (size_t index = 0; index < system.axiom.length; index++)
    {
        Symbol symbol = system.axiom.symbols[index];
        Direction direction = get_symbol_direction(symbol, move_map);
        switch (direction) {
            case UP:
                turtle = move_point_in_rad_direction(turtle, turtle_direction);
                add_point_to_list(turtle, polyline);
                break;
            case ROTATE_LEFT:
                turtle_direction += move_map.rotation_angle;
                if (turtle_direction > (float) (2 * M_PI))
                    turtle_direction -= (float) (2 * M_PI);
                break;
            case ROTATE_RIGHT:
                turtle_direction -= move_map.rotation_angle;
                if (turtle_direction < 0)
                    turtle_direction += (float) (2 * M_PI);
                break;
            default:
                break;
        }
    }
}

void render_polyline_to_canvas(PointList polyline, Canvas * canvas)
{
    Colour clear_colour = create_colour_greyscale(1);
    clear_canvas(canvas, clear_colour);
    normalize_point_list(&polyline);
    for (size_t index = 0; index < polyline.length - 1; index++)
    {
        Point start = polyline.points[index];
        Point end = polyline.points[index+1];
        render_line_to_canvas(start, end, canvas);
    }
}

void render_line_to_canvas(Point start, Point end, Canvas * canvas)
{
    Colour draw_colour = create_colour(0, 0.2f, 0);

    // Flip Y axis for a correct image axis
    start.y = 1 - start.y;
    end.y = 1 - end.y;

    // Scale normalized points to canvas locations.
    Point canvas_size = {canvas->width, canvas->height};
    start = multiply_points(start, canvas_size);
    end = multiply_points(end, canvas_size);

    // Bresenham's algorithm for drawing a line on a raster
    Point delta = subtract_points(end, start);
    Point abs_delta = {fabsf(delta.x)*2, fabsf(delta.y)*2};
    Point sign_delta = {signf(delta.x), signf(delta.y)};
    Point point = start;
    if (abs_delta.x > abs_delta.y) // x increases faster than y
    {
        float decision = abs_delta.y - abs_delta.x / 2;
        while (true)
        {
            // Break if we're over our bounds.
            if (start.x < end.x && point.x > end.x || start.x > end.x && point.x < end.x)
                break;

            set_pixel(canvas, draw_colour, (size_t) point.y, (size_t) point.x);

            if (decision >= 0)
            {
                point.y += sign_delta.y;
                decision -= abs_delta.x;
            }
            point.x += sign_delta.x;
            decision += abs_delta.y;
        }
    }
    else // y increases faster than x
    {
        float decision = abs_delta.x - abs_delta.y / 2;
        while (true)
        {
            // Break if we're over our bounds.
            if (start.y < end.y && point.y > end.y || start.y > end.y && point.y < end.y)
                break;

            set_pixel(canvas, draw_colour, (size_t) point.y, (size_t) point.x);

            if (decision >= 0)
            {
                point.x += sign_delta.x;
                decision -= abs_delta.y;
            }
            point.y += sign_delta.y;
            decision += abs_delta.x;
        }
    }
}