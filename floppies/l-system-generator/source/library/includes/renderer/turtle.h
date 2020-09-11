#ifndef TURTLE_H
#define TURTLE_H

#include "system/system.h"
#include "renderer/canvas.h"

void render_system_to_canvas(LSystem system, Canvas * canvas);
void build_polyline_from_system(PointList * polyline, LSystem system);
void render_polyline_to_canvas(PointList polyline, Canvas * canvas);

#endif