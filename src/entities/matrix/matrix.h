#ifndef RT_CHALLENGE_MATRIX_H
#define RT_CHALLENGE_MATRIX_H

#include "../../../heads_global/minirt.h"


typedef struct  t_matrix
{
    double **matrix;
    int h;
    int w;
}               s_matrix;

s_matrix    *matrix_matrix(int h, int w);
s_matrix    *matrix_identity(int range);
s_matrix    *tuple_to_matrix(s_tuple *t);
int         matrix_equals(s_matrix *m1, s_matrix *m2);
void        matrix_free(s_matrix *m);
s_matrix    *matrix_copy(s_matrix *m);

s_matrix    *matrix_multiply(s_matrix *m1, s_matrix *m2);
s_matrix    *matrix_transpose(s_matrix *m);
double      matrix_determinant(s_matrix *m);
s_matrix    *matrix_sub(s_matrix *m,  int column,  int row);

double      matrix_minor(s_matrix *m, int from, int to);
double      matrix_cofactor(s_matrix *m, int from, int to);
s_matrix    *matrix_invert(s_matrix *m);

s_tuple     *tuple_apply_trans_matrix(s_matrix *trans_matrix, s_tuple *tup);

s_matrix    *matrix_translate(double x, double y, double z);
s_matrix    *matrix_scale(double x, double y, double z);
s_matrix    *matrix_x_rotate(double r);
s_matrix    *matrix_y_rotate(double r);
s_matrix    *matrix_z_rotate(double r);
s_matrix    *rotate_axis_angle(s_tuple *u, double angle);
s_matrix    *rotate_align(s_tuple *v1, s_tuple *v2);
s_matrix    *view_transform(s_tuple *from, s_tuple *to, s_tuple *up);

#endif //RT_CHALLENGE_MATRIX_H
