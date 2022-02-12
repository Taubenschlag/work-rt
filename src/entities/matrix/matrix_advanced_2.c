#include "../../../heads_global/minirt.h"

s_matrix    *invert(double determinant, s_matrix *m, s_matrix *inverted)
{
    int         i;
    int         j;
    s_matrix    *cofactors;
    double      diag;

    i = -1;
    cofactors = matrix_matrix(m->h, m->w);
    while (++i < m->h)
    {
        j = -1;
        while (++j < m->w)
            cofactors->matrix[i][j] = matrix_cofactor(m, i, j);
    }
    inverted = matrix_transpose(cofactors);
    i = -1;
    while (++i < m->h)
    {
        j = -1;
        while (++j < m->w)
        {
            diag = inverted->matrix[i][j] / determinant;
            inverted->matrix[i][j] = diag;
        }
    }
    return (inverted);
}

s_matrix    *matrix_invert(s_matrix *m)
{
    double      determinant;
    s_matrix    *inverted;

    inverted = NULL;
    determinant = matrix_determinant(m);
    if (determinant)
        inverted = invert(determinant, m, inverted);
    if(!inverted)
        return NULL;
    return (inverted);
}

s_tuple     *tuple_apply_trans_matrix(s_matrix *trans_matrix, s_tuple *tup)
{
     s_matrix    *source_tuple_converted;
    s_matrix    *product;
    s_tuple     *res;
    int         need_free;

    source_tuple_converted = tuple_to_matrix(tup);
    if (trans_matrix)
        product = matrix_multiply(trans_matrix, source_tuple_converted);
    else
        product = source_tuple_converted;
    need_free = trans_matrix ? 0 : 1;
    res = tuple_point(
            product->matrix[0][0], product->matrix[1][0],
            product->matrix[2][0]);
    if (tuple_is_vector(tup))
        res->type = IS_VECTOR;
    if (trans_matrix)
        matrix_free(product);
    if (need_free)
    {
        matrix_free(trans_matrix);
        matrix_free(source_tuple_converted);
    }
    free(tup);
    return (res);
}

s_matrix    *vt_combine_matrix(s_tuple *left, s_tuple *true_up, s_tuple *forward)
{
    s_matrix *res;

    res = matrix_identity(4);
    res->matrix[0][0] = left->x;
    res->matrix[0][1] = left->y;
    res->matrix[0][2] = left->z;
    res->matrix[1][0] = true_up->x;
    res->matrix[1][1] = true_up->y;
    res->matrix[1][2] = true_up->z;
    res->matrix[2][0] = -1 * forward->x;
    res->matrix[2][1] = -1 * forward->y;
    res->matrix[2][2] = -1 * forward->z;
    tuple_free(forward);
    tuple_free(left);
    tuple_free(true_up);
    return (res);
}

s_matrix    *view_transform(s_tuple *from, s_tuple *to, s_tuple *up)
{
    s_tuple *forward;
    s_tuple *left;
    s_tuple *tmp;
    s_matrix *res;
    s_matrix *view_matrix;

    tmp = tuple_substract(to, tuple_copy(from));
    forward = tuple_normalize(tmp);
    tmp = tuple_normalize(up);
    left = tuple_cross_product(forward, tmp);
    tuple_free(tmp);
    from = tuple_negate(from);
    res = vt_combine_matrix(left, tuple_cross_product(left, forward), forward);
    view_matrix = matrix_multiply(
            res, matrix_translate(from->x, from->y, from->z));
    tuple_free(from);
    return(view_matrix);
}
