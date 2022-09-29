#include "../../../heads_global/minirt.h"

s_tuple     *tuple_negate(s_tuple *t)
{
    s_tuple *res;

    res =  (s_tuple*)malloc(sizeof(s_tuple));
    res->x = t->x * -1;
    res->y = t->y * -1;
    res->z = t->z * -1;
    res->type = t->type * -1;
    tuple_free(t);
    return (res);
}

double      tuple_length(s_tuple *t)
{
    return (
            sqrt(
                    t->x * t->x +
                    t->y * t->y +
                    t->z * t->z +
                    t->type * t->type)
            );
}

s_tuple     *tuple_normalize(s_tuple *t)
{
    double  length;
    s_tuple *n;

    length = tuple_length(t);
    n = tuple_vector(
            t->x / length,
            t->y / length,
            t->z / length);
    tuple_free(t);
    return (n);
}

double      tuple_dot_product(s_tuple *t1, s_tuple *t2)
{
    return (
            t1->x * t2->x +
            t1->y * t2->y +
            t1->z * t2->z
            );
}

s_tuple     *tuple_cross_product(s_tuple *t1, s_tuple *t2)
{
    return (
            tuple_vector(
                    t1->y * t2->z - t1->z * t2->y,
                    t1->z * t2->x - t1->x * t2->z,
                    t1->x * t2->y - t1->y * t2->x)
            );
}