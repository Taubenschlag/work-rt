#include "../../../heads_global/minirt.h"

int cheaty_free(s_tuple *tuple)
{
    free(tuple);
    return (1);
}

s_tuple     *tuple_multiply(s_tuple *t1, s_tuple *t2)
{
    s_tuple *t;

    t =  (s_tuple*)malloc(sizeof(s_tuple));
    t->x = t1->x * t2->x;
    t->y = t1->y * t2->y;
    t->z = t1->z * t2->z;
    t->type = t1->type * t2->type;
    return (t);
}

s_tuple     *tuple_reflect(s_tuple *v_in, s_tuple *v_normal)
{
    s_tuple *v_out;
    s_tuple *tmp;

   tmp = tuple_scalar_multiply(tuple_copy(v_normal), tuple_dot_product(v_in, v_normal) * 2);
   v_out = tuple_substract(v_in, tmp);
    return (v_out);
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

s_tuple     *tuple_copy(s_tuple *t)
{
    s_tuple *res;

    res = tuple_point(t->x, t->y, t->z);
    res->type = t->type;
    return (res);
}