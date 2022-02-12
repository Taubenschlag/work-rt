#include "../../../heads_global/minirt.h"

s_matrix    *matrix_translate(double x, double y, double z)
{
    s_matrix *trans;
    trans = matrix_identity(4);
    trans->matrix[0][3] = x;
    trans->matrix[1][3] = y;
    trans->matrix[2][3] = z;
    return (trans);
}

s_matrix    *matrix_scale(double x, double y, double z)
{
    s_matrix    *scl;

    scl = matrix_identity(4);
    scl->matrix[0][0] = x;
    scl->matrix[1][1] = y;
    scl->matrix[2][2] = z;
    return (scl);
}

s_matrix    *matrix_x_rotate(double r)
{
    s_matrix    *scl;

    scl = matrix_identity(4);
    if (r != 0)
    {
        scl->matrix[1][1] = cos(r);
        scl->matrix[1][2] = -1 * sin(r);
        scl->matrix[2][1] = sin(r);
        scl->matrix[2][2] = cos(r);
    }
    return (scl);
}

s_matrix    *matrix_y_rotate(double r)
{
    s_matrix    *scl;

    scl = matrix_identity(4);
    if (r != 0)
    {
        scl->matrix[0][0] = cos(r);
        scl->matrix[2][0] = -1 * sin(r);
        scl->matrix[0][2] = sin(r);
        scl->matrix[2][2] = cos(r);
    }
    return (scl);
}

s_matrix    *matrix_z_rotate(double r)
{
    s_matrix    *scl;

    scl = matrix_identity(4);
    if (r != 0)
    {
        scl->matrix[0][0] = cos(r);
        scl->matrix[0][1] = -1 * sin(r);
        scl->matrix[1][0] = sin(r);
        scl->matrix[1][1] = cos(r);
    }
    return (scl);
}