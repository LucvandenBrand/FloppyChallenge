#ifndef POINT_H
#define POINT_H

#include <stdlib.h>

typedef struct
{
    float x;
    float y;
} Point;

typedef struct
{
    Point * points;
    size_t length;
    size_t space;
} PointList;

PointList alloc_empty_point_list();
void free_point_list(PointList * list);
void add_point_to_list(Point point, PointList * list);

#endif