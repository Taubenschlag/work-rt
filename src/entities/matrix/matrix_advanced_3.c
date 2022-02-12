#include "../../../heads_global/minirt.h"

s_matrix *rotate_axis_angle(s_tuple *u, double angle)
{
    double sin_a;
    double cos_a;
    double one_min_cos_a;
    s_matrix *ret;

    sin_a = sin(angle);
    cos_a = cos(angle);
    one_min_cos_a = 1 - cos_a;
    ret = matrix_identity(4);

    ret->matrix[0][0] = (u->x * u->x * one_min_cos_a) + cos_a;
    ret->matrix[0][1] = (u->y * u->x * one_min_cos_a) - (sin_a * u->z);
    ret->matrix[0][2] = (u->z * u->x * one_min_cos_a) + (sin_a * u->y);
    ret->matrix[1][0] = (u->x * u->y * one_min_cos_a) + (sin_a * u->z);
    ret->matrix[1][1] = (u->y * u->y * one_min_cos_a) + cos_a;
    ret->matrix[1][2] = (u->z * u->y * one_min_cos_a) - (sin_a * u->x);
    ret->matrix[2][0] = (u->x * u->z * one_min_cos_a) - (sin_a * u->y);
    ret->matrix[2][1] = (u->y * u->z * one_min_cos_a) + (sin_a * u->x);
    ret->matrix[2][2] = (u->z * u->z * one_min_cos_a) + cos_a;
    return (ret);
}

s_matrix *rotate_align(s_tuple *v1, s_tuple *v2)
{
    s_tuple *axis;
    double  dot;
    double  angle;
    s_matrix *res;

    axis = tuple_normalize(tuple_cross_product(v1, v2));
    dot = tuple_dot_product(v1, v2);
    angle = acos(dot);
    res = rotate_axis_angle(axis, angle);
    tuple_free(v1);
    tuple_free(axis);
    return (res);
}

double      matrix_minor(s_matrix *m, int from, int to)//todo assert 3x3
{
    s_matrix *sub;
    double res;

    sub = matrix_sub(m, from, to);
    res = matrix_determinant(sub);
    matrix_free(sub);
    return (res);
}

double      matrix_cofactor(s_matrix *m, int from, int to)
{
    double minor;

    minor = matrix_minor(m, from, to);
    return (((from + to) % 2) ? minor * -1 :  minor);
}