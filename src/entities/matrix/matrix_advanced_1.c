#include "../../../heads_global/minirt.h"

s_matrix    *matrix_multiply(s_matrix *m1, s_matrix *m2)
{
    s_matrix *res;
    int i;
    int j;
    int l;
    double tmp;

    res = matrix_matrix(min(m1->h, m2->h), min(m1->w, m2->w));
    i = -1;
    while (++i < res->h)
    {
        j = -1;
        while (++j < res->w)
        {
            l = 0;
            tmp = 0;
            while (l < m1->w && l < m2->h)
            {
                tmp += m1->matrix[i][l] * m2->matrix[l][j];
                l++;
            }
            res->matrix[i][j] = tmp;
        }
    }
    matrix_free(m1);
    matrix_free(m2);
    return (res);
}

s_matrix    *matrix_transpose(s_matrix *m)
{
    s_matrix *res;
    int i;
    int j;

    res = matrix_matrix(m->h, m->w);
    i = 0;
    while (i < res->h)
    {
        j = 0;
        while (j < res->w)
        {
            res->matrix[i][j] = m->matrix[j][i];
            j++;
        }
        i++;
    }
    matrix_free(m);
    return (res);
}

double      matrix_determinant(s_matrix *m)
{
    int column;
    double determinant;

    determinant = 0;
    column = -1;
    if (m->h == 2 && m->w == 2)
        determinant = m->matrix[0][0] * m->matrix[1][1] -
                m->matrix[0][1] * m->matrix[1][0];
    else
        while (++column < m->w)
            determinant += m->matrix[0][column] *
                    matrix_cofactor(m, 0, column);
    return (determinant);
}

s_matrix    *matrix_sub(s_matrix *m, int column,  int row)
{
    s_matrix *res;
    int i;
    int j;
    int i_skip;
    int j_skip;

    res = matrix_matrix(m->h - 1, m->w - 1);
    i = 0;
    i_skip = 0;
    while (i < m->h && !(i == column && column == m->h - 1))
    {
        j = 0;
        j_skip = 0;
        if (i == column && ++i)
            i_skip = 1;
        while (j < m->w && !(j == row && row == m->w - 1))
        {
            if (j == row && ++j)
                j_skip = 1;
            res->matrix[i - i_skip][j - j_skip] = m->matrix[i][j];
            j++;
        }
        i++;
    }
    return (res);
}

s_matrix    *matrix_copy(s_matrix *m)
{
    s_matrix *ret;
    int i;
    int j;

    ret = matrix_matrix(m->h, m->w);
    i = -1;
    while (++i < ret->h)
    {
        j = -1;
        while (++j < ret->w)
            ret->matrix[i][j] = m->matrix[i][j];
    }
    return (ret);
}