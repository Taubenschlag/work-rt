#include "../../../heads_global/minirt.h"

void                add_intersection(s_intersection *new_elem,
        s_intersection_list **list)
{
    s_intersection_list *nl;
    int i;

    i = -1;
    nl = intersection_list_make((*list)->size + 1);
    while (++i < (*list)->size)
        nl->list[i] = (*list)->list[i];
    nl->list[i] = new_elem;
    if ((*list)->list)
        free((*list)->list);
    free(*list);
    *list = nl;
}

s_intersection_list* intersect_world(s_ray *r, s_world *w)
{
    s_intersection_list *merged;
    s_intersection_list *unsorted[w->shape_counter];
    int i;
    int j;
    int size;

    i = w->shape_counter;
    size = 0;
    while (--i >= 0)
    {
        unsorted[i] = intersect_shape(w->shapes[i], r);
        size += unsorted[i]->size;
    }
    merged = intersection_list_make(size);
    size = -1;
    i = -1;
    while (++i < w->shape_counter)
    {
        j = -1;
        while (++j < unsorted[i]->size)
            merged->list[++size] = unsorted[i]->list[j];
        free(unsorted[i]->list);
        free(unsorted[i]);
    }
    return (merged);
}

s_computations      *precomp(s_intersection *i, s_ray *r)
{
    s_computations *comps;
    s_tuple *tmp;

    comps = (s_computations *)malloc(sizeof(s_computations));
    comps->t = i->t;
    comps->shape = i->shape;
    comps->point = ray_position(r, i->t);
    comps->eyev = tuple_negate(tuple_copy(r->dir));
    comps->normv = shape_normal_at(i->shape, comps->point);
    if (tuple_dot_product(comps->normv, comps->eyev) < 0)
    {
        comps->inside = 1;
        tmp = tuple_negate(tuple_copy(comps->normv));
        tuple_free(comps->normv);
        comps->normv = tmp;
    }
    else
        comps->inside = 0;
    comps->overpoint = tuple_add(tuple_copy(comps->point),
            tuple_scalar_multiply(tuple_copy(comps->normv),  0.0001));
    return (comps);
}

s_tuple *shade_hit(s_world *w, s_computations *cs, s_light *current)
{
    return (lightning(
            make_l_p(cs->shape->matrl, current, cs->point, cs->eyev, cs->normv),
            in_shadow(w, cs->overpoint, current)));
}

s_tuple             *color_at(s_world *w, s_ray *r)
{
    s_intersection_list *l;
    s_intersection  *i;
    s_computations *c;
    s_tuple *color;
    int j;

    j = -1;
    l = intersect_world(r, w);
    i = hit(l);
    if (!i)
        color = tuple_color(0, 0, 0);
    else
    {
        c = precomp(i, r);
        color = shade_hit(w, c, w->ambienace);
        free(c);
        while (++j < w->lights_counter)
        {
            c = precomp(i, r);
            color = tuple_add(color, shade_hit(w, c, w->lights[j]));
            free(c);
        }
    }
    free(i);
    return (color);
}