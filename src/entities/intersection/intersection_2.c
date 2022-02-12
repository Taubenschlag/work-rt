#include "../../../heads_global/minirt.h"

s_intersection_list * cyl_int_cap(s_shape *c, s_ray *r, s_intersection_list *l)
{
    double t;
    if (!(((s_cylinder *)c->shape)->closed) || fabs(r->dir->y) < 0.00001)
        return (l);
    t = (((s_cylinder *)c->shape)->min - r->origin->y) / r->dir->y;
    if (check_cap(r, t))
        add_intersection(intersect_make_shape(c, t), &l);
    t = (((s_cylinder *)c->shape)->max - r->origin->y) / r->dir->y;
    if (check_cap(r, t))
        add_intersection(intersect_make_shape(c, t), &l);
    return(l);
}

s_intersection_list *intersection_ray_cylinder(s_shape *s, s_ray *ray)
{
    double  a;
    double  b;
    double  disc;
    double t[2];
    s_intersection_list  *ret;

    a = ray->dir->x * ray->dir->x +
        ray->dir->z * ray->dir->z;
    ret = intersection_list_make(0);
    if (a < 0.00001)
        return (cyl_int_cap(s, ray, ret));
    b = 2 * ray->dir->x * ray->origin->x +
        2 * ray->dir->z * ray->origin->z;
    disc = b * b - 4 * a * (ray->origin->x * ray->origin->x +
            ray->origin->z * ray->origin->z - 1);
    if (disc < 0)
        return (ret);
    t[0] = (-1 * b - sqrt(disc)) / (2 * a);
    t[1] = (-1 * b + sqrt(disc)) / (2 * a);
    a = ray->origin->y + mins(t, 2) * ray->dir->y;
    if (((s_cylinder *)s->shape)->min < a && a < ((s_cylinder *)s->shape)->max)
        add_intersection(intersect_make_shape(s, mins(t, 2)), &ret);
    a = ray->origin->y + maxs(t, 2) * ray->dir->y;
    if (((s_cylinder *)s->shape)->min < a && a < ((s_cylinder *)s->shape)->max)
        add_intersection(intersect_make_shape(s, maxs(t, 2)), &ret);
    return (cyl_int_cap(s, ray, ret));
}

s_intersection_list *co_intrs_cap(s_shape *c, s_ray *r, s_intersection_list *l)
{
    double t;
    if (!(((s_cone *)c->shape)->closed) || fabs(r->dir->y) < 0.0000001)
        return (l);
    t = (((s_cone *)c->shape)->min - r->origin->y) / r->dir->y;
    if (check_cap_cone_min(r, t, ((s_cone *) c->shape)->min))
        add_intersection(intersect_make_shape(c, t), &l);
    t = (((s_cone *)c->shape)->max - r->origin->y) / r->dir->y;
    if (check_cap_cone_max(r, t, ((s_cone *) c->shape)->max))
        add_intersection(intersect_make_shape(c, t), &l);
    return(l);
}

void    handle_cone_inters(s_ray *ray, s_shape *s,  s_intersection_list  **ret,
                           double *t_s)
{
    double a;


    a = ray->origin->y + mins(t_s, 2) * ray->dir->y;
    if (((s_cone *)s->shape)->min < a && a < ((s_cone *)s->shape)->max)
        add_intersection(intersect_make_shape(s, mins(t_s, 2)), ret);
    a = ray->origin->y + maxs(t_s, 2) * ray->dir->y;
    if (((s_cone *)s->shape)->min < a && a < ((s_cone *)s->shape)->max)
        add_intersection(intersect_make_shape(s, maxs(t_s, 2)), ret);
    free(t_s);
}

s_intersection_list *intersection_ray_cone(s_shape *s, s_ray *ray)
{
    double  temp[4];
    double  *t_s;
    s_intersection_list  *ret;

    ret = intersection_list_make(0);
    temp[0] = ray->dir->x * ray->dir->x - ray->dir->y *
            ray->dir->y + ray->dir->z * ray->dir->z;
    temp[1] = 2 * ray->dir->x * ray->origin->x - 2 * ray->dir->y *
            ray->origin->y + 2 * ray->dir->z * ray->origin->z;
    temp[2] = ray->origin->x * ray->origin->x - ray->origin->y *
            ray->origin->y + ray->origin->z * ray->origin->z;
    if (fabs(temp[0]) < 0.000001 )
    {
        if (fabs(temp[1]) > 0.0000001)
            add_intersection(intersect_make_shape(s, -1 *
            temp[2] / (2 * temp[1])), &ret);
        return (co_intrs_cap(s, ray, ret));
    }
    temp[3] = temp[1] * temp[1] - 4 * temp[0] * temp[2];
    if (temp[3] < 0)
        return (ret);
    t_s = (double *)malloc(sizeof(double) * 2);
    t_s[0] = (-1 * temp[1] - sqrt(temp[3])) / (2 * temp[0]);
    t_s[1] = (-1 * temp[1] + sqrt(temp[3])) / (2 * temp[0]);
    handle_cone_inters(ray, s, &ret, t_s);
    return (co_intrs_cap(s, ray, ret));
}
