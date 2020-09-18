#ifndef TURTLE_H
#define TURTLE_H

#include "system/system.h"
#include "renderer/canvas.h"
#include "renderer/movemap.h"
#include "math/point.h"

void render_system_to_canvas(LSystem system, MoveMap move_map, Canvas * canvas);
void build_polyline_from_system(PointList * polyline, MoveMap move_map, LSystem system);
void render_polyline_to_canvas(PointList polyline, Canvas * canvas);
void render_line_to_canvas(Point start, Point end, Canvas * canvas);

#endif