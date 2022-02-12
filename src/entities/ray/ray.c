#include "../../../heads_global/minirt.h"

s_ray   *ray_ray(s_tuple *origin, s_tuple *direction)
{
    s_ray *ray;

    ray = (s_ray*)malloc(sizeof(s_ray));
    ray->origin = origin;
    ray->dir = direction;
    return (ray);
}

void    ray_free(s_ray *ray)
{
        tuple_free((ray->origin));
        tuple_free((ray->dir));
        free(ray);
}

s_ray   *ray_transform(s_ray *ray, s_matrix *m)
{
    s_matrix *m1;

    m1 = matrix_copy(m);

    return (ray_ray(
            tuple_apply_trans_matrix(m1, tuple_copy(ray->origin)),
            tuple_apply_trans_matrix(m, tuple_copy(ray->dir))));
}

s_tuple *ray_position(s_ray *ray, double t)
{
    return (tuple_add(
            tuple_copy(ray->origin),
            tuple_scalar_multiply(tuple_copy(ray->dir), t)));
}