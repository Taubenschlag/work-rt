#include "../../../../heads_global/minirt.h"

s_square      *square()
{
    s_square *ret;
    ret = (s_square*)malloc(sizeof(s_square));
    ret->t1 = triangle_coordinates(
            tuple_point(-1, 1, 0),
            tuple_point(-1, -1, 0),
            tuple_point(1, 1, 0));
    ret->t2 = triangle_coordinates(
            tuple_point(1, -1, 0),
            tuple_point(1, 1, 0),
            tuple_point(-1, -1, 0));
    return (ret);
}

s_tuple       *square_normale_at()
{
    return (tuple_vector(0, 0, 1));
}

void          free_square(s_square *t)
{
    free_triangle(t->t1);
    free_triangle(t->t2);
    free(t);
}