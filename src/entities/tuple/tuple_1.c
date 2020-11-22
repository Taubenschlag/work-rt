#include "tuple.h"

s_tuple     *tuple_vector(double x, double y, double z)
{
    s_tuple *t;

    t = (s_tuple*)malloc(sizeof(s_tuple));
    t->x = x;
    t->y = y;
    t->z = z;
    t->type = IS_VECTOR;
    return (t);
}

s_tuple     *tuple_point(double x, double y, double z)
{
    s_tuple *t;

    t =  (s_tuple*)malloc(sizeof(s_tuple));
    t->x = x;
    t->y = y;
    t->z = z;
    t->type = IS_POINT;
    return (t);
}

s_tuple     *tuple_color(double r, double g, double b)
{
    s_tuple *t;

    t = (s_tuple*)malloc(sizeof(s_tuple));
    t->x = r;
    t->y = g;
    t->z = b;
    t->type = 2;
    return (t);
}