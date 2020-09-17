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
void normalize_point_list(PointList * list);
void get_list_bounds(PointList list, Point * min, Point * max);
Point min_point(Point first_point, Point second_point);
Point max_point(Point first_point, Point second_point);
float get_max_point_length(PointList list);
float point_length(Point point);
Point divide_point(Point point, float scalar);
Point multiply_points(Point first_point, Point second_point);
Point move_point_in_rad_direction(Point point, float direction);
Point subtract_points(Point first_point, Point second_point);
Point add_points(Point first_point, Point second_point);


#endif