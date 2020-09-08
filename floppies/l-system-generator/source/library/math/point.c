#include "math/point.h"
#include "memory/safe_alloc.h"

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