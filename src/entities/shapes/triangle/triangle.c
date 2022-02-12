#include "../../../../heads_global/minirt.h"

s_triangle      *triangle_coordinates(s_tuple *a, s_tuple *b, s_tuple *c)
{
    s_triangle *tr;
    tr = (s_triangle *)malloc(sizeof(s_triangle));
    tr->a = a;
    tr->b = b;
    tr->c = c;
    tr->e1 = tuple_substract(tuple_copy(b), tuple_copy(a));
    tr->e2 = tuple_substract(tuple_copy(c), tuple_copy(a));
    tr->n = tuple_normalize(tuple_cross_product(tr->e1, tr->e2));
    return (tr);
}

void            free_triangle(s_triangle *t)
{
    tuple_free(t->a);
    tuple_free(t->b);
    tuple_free(t->c);
    tuple_free(t->e1);
    tuple_free(t->e2);
    tuple_free(t->n);
    free(t);
}

s_tuple         *triangle_normale_at(s_triangle *t)
{
    return (tuple_copy(t->n));
}