#ifndef TUPLE_H
#define TUPLE_H
#include "../../../heads_global/minirt.h"

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

void        tuple_free(s_tuple *tuple);
int cheaty_free(s_tuple *tuple);

int         tuple_is_vector(s_tuple *tuple);

int         tuple_equals(s_tuple *t1, s_tuple *t2);
s_tuple     *tuple_add(s_tuple *t1, s_tuple *t2);
s_tuple     *tuple_substract(s_tuple *t1, s_tuple *t2);
s_tuple     *tuple_scalar_multiply(s_tuple *t, double scale);

s_tuple     *tuple_negate(s_tuple *t);
double      tuple_length(s_tuple *t);
s_tuple     *tuple_normalize(s_tuple *t);
double      tuple_dot_product(s_tuple *t1, s_tuple *t2);
s_tuple     *tuple_cross_product(s_tuple *t1, s_tuple *t2);

s_tuple     *tuple_multiply(s_tuple *t1, s_tuple *t2);
s_tuple     *tuple_reflect(s_tuple *v_in, s_tuple *v_normal);
s_tuple     *tuple_copy(s_tuple *t);

#endif 