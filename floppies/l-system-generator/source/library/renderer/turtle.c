#include <math.h>
#include "math/point.h"
#include "renderer/turtle.h"

void render_system_to_canvas(LSystem system, Canvas * canvas)
{
    // TODO: Actually render the system to the canvas.
    PointList polyline = alloc_empty_point_list();
    build_polyline_from_system(&polyline, system);
    render_polyline_to_canvas(polyline, canvas);
    free_point_list(&polyline);
}

void build_polyline_from_system(PointList * polyline, LSystem system)
{
    Point turtle = {0, 0};
    float turtle_direction =  M_PI / 2;
    add_point_to_list(turtle, polyline);
    for (size_t index = 0; index < system.axiom.length; index++)
    {
        Symbol symbol = system.axiom.symbols[index];
        // The following part should not be hardcoded, but it is.
        // It would be best to have an interpretation map in the l-system definition.
        if (symbol == 'A' || symbol == 'B')
        {
            turtle = move_point_in_rad_direction(turtle, turtle_direction);
            add_point_to_list(turtle, polyline);
        }
        else if (symbol == '+')
        {
            turtle_direction -= (float) (M_PI / 3);
            if (turtle_direction < 0)
                turtle_direction += (float) (2 * M_PI);
        }
        else if (symbol == '-')
        {
            turtle_direction += (float) (M_PI / 3);
            if (turtle_direction > (float) (2 * M_PI))
                turtle_direction -= (float) (2 * M_PI);
        }
    }
}

void render_polyline_to_canvas(PointList polyline, Canvas * canvas)
{

}