#ifndef TUPLE_H
#define TUPLE_H
#include "../../../heads_global/minirt.h"

#define IS_COLOR    2
#define IS_POINT    1
#define IS_VECTOR   0

typedef struct  t_tuple
{
    double  x;
    double  y;
    double  z;
    int     type;
}               s_tuple;

s_tuple     *tuple_vector(double x, double y, double z);
s_tuple     *tuple_point(double x, double y, double z);
s_tuple     *tuple_color(double r, double g, double b);

#endif