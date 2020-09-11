#include <float.h>
#include <math.h>
#include "math/point.h"
#include "memory/safe_alloc.h"
#include "math/bounds.h"

PointList alloc_empty_point_list()
{
    PointList list;
    list.length = 0;
    list.space = 2;
    list.points = safe_malloc(sizeof(Point) * list.space);
    return list;
}

void free_point_list(PointList * list)
{
    free(list->points);
    list->points = NULL;
    list->space = 0;
    list->length = 0;
}

void add_point_to_list(Point point, PointList * list)
{
    list->points[list->length++] = point;
    if (list->length == list->space)
    {
        list->space *= 2;
        list->points = safe_realloc(list->points, sizeof(Point) * list->space);
    }
}

void normalize_point_list(PointList * list)
{
    Point min, max;
    get_list_bounds(*list, &min, &max);
    Point diagonal = subtract_points(max, min);
    float diagonal_length = point_length(diagonal);

    for (size_t index = 0; index < list->length; index++)
    {
        Point point = list->points[index];
        point = subtract_points(point, min);
        list->points[index] = divide_point(point, diagonal_length);
    }
}

void get_list_bounds(PointList list, Point * min, Point * max)
{
    Point current_min = {FLT_MAX, FLT_MAX};
    Point current_max = {FLT_MIN, FLT_MIN};
    for (size_t index = 0; index < list.length; index++)
    {
        Point point = list.points[index];
        current_min = min_point(point, current_min);
        current_max = max_point(point, current_max);
    }
    *min = current_min;
    *max = current_max;
}

Point min_point(Point first_point, Point second_point)
{
    Point min;
    min.x = first_point.x < second_point.x ? first_point.x : second_point.x;
    min.y = first_point.y < second_point.y ? first_point.y : second_point.y;
    return min;
}

Point max_point(Point first_point, Point second_point)
{
    Point max;
    max.x = first_point.x > second_point.x ? first_point.x : second_point.x;
    max.y = first_point.y > second_point.y ? first_point.y : second_point.y;
    return max;
}

float get_max_point_length(PointList list)
{
    float max_length = FLT_MIN;
    for (size_t index = 0; index < list.length; index++)
    {
        Point point = list.points[index];
        float length = point_length(point);
        max_length = length > max_length ? length : max_length;
    }
    return max_length;
}

float point_length(Point point)
{
    return sqrtf(point.x * point.x + point.y * point.y);
}

Point divide_point(Point point, float scalar)
{
    Point divided_point = {point.x / scalar, point.y / scalar};
    return divided_point;
}

Point move_point_in_rad_direction(Point point, float direction)
{
    Point movement = {cosf(direction), sinf(direction)};
    Point new_point = add_points(point, movement);
    // Cos and Sin can have precision problems, so snap to 0 if low enough
    new_point.x = snap_to_value(new_point.x, 0, 0.1f);
    new_point.y = snap_to_value(new_point.y, 0, 0.1f);
    // Same goes for 1.
    new_point.x = snap_to_value(new_point.x, 1, 0.1f);
    new_point.y = snap_to_value(new_point.y, 1, 0.1f);
    return new_point;
}

Point add_points(Point first_point, Point second_point)
{
    Point point = {first_point.x + second_point.x, first_point.y + second_point.y};
    return point;
}

Point subtract_points(Point first_point, Point second_point)
{
    Point point = {first_point.x - second_point.x, first_point.y - second_point.y};
    return point;
}