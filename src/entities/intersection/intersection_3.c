#include "../../../heads_global/minirt.h"

int in_shadow(s_world *w, s_tuple *p, s_light *current_light)
{
    s_tuple *v;
    double dist;
    s_tuple *direction;
    s_ray *ray;
    s_intersection *h;

    v = tuple_substract(tuple_copy(current_light->position),tuple_copy(p));
    dist = tuple_length(v);
    direction = tuple_normalize(v);
    ray = ray_ray(p, direction);
    h = hit(intersect_world(ray, w));
    ray_free(ray);
    if (h && (dist - h->t) > 0.00001)
    {
        free(h);
        return (1);
    }
    if (h)
        free(h);
    return (0);
}

s_intersection_list *intersection_ray_plane(s_shape *s, s_ray *ray)
{
    s_intersection_list  *ret;
    if (fabs(ray->dir->y) < 0.000001 )
        return (intersection_list_make(0));
    else
    {
        ret = intersection_list_make(1);
        ret->list[0] =
                intersect_make_shape(s,(-1 * ray->origin->y) / ray->dir->y);
        return (ret);
    }
}

s_intersection_list *intersection_ray_nsphere(s_shape *s, s_ray *ray)
{
    s_tuple *sphere_ray;
    double  a;
    double  b;
    double  dis;
    s_intersection_list  *ret;

    sphere_ray = tuple_substract(tuple_copy(ray->origin),
                                 tuple_copy(((s_nsphere*)s->shape)->centre));
    a = tuple_dot_product(ray->dir, ray->dir);
    b = 2 * tuple_dot_product(ray->dir, sphere_ray);
    dis = b * b - 4 * a * (tuple_dot_product(sphere_ray, sphere_ray) - 1);
    tuple_free(sphere_ray);
    if (dis < 0)
        return (intersection_list_make(0));
    ret = intersection_list_make(2);
    ret->list[0] = intersect_make_shape(s, (-1 * b - sqrt(dis)) / (2 * a));
    ret->list[1] = intersect_make_shape(s, (-1 * b + sqrt(dis)) / (2 * a));
    return (ret);
}
