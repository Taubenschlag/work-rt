/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/11 17:16:55 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# include "../../../heads_global/minirt.h"

# define M_MAX 4
/*
typedef struct matrix
{
	double	**matrix;
	int		h;
	int		w;
}	t_matrix;
*/
typedef struct matrix
{
	double	mtx[M_MAX][M_MAX];
	int		h;
	int		w;
}	t_matrix;

void	matrix_matrix(t_matrix *m, int h, int w);
void	matrix_identity(t_matrix *m, int range);
void	tuple_to_matrix(t_matrix *m, t_tuple *t);
void	matrix_copy(t_matrix *dest, t_matrix *m);

void	matrix_multiply(t_matrix *res, t_matrix *m1, t_matrix *m2);
void	matrix_transpose(t_matrix *res, t_matrix *m);
double		matrix_determinant(t_matrix *m);
void	matrix_sub(t_matrix *res, t_matrix *m, int column, int row);

double	matrix_minor(t_matrix *sub, t_matrix *m, int from, int to);
double	matrix_cofactor(t_matrix *sub, t_matrix *m, int from, int to);
void	matrix_invert(t_matrix *inverted, t_matrix *m);

t_tuple		*tuple_apply_trans_matrix(t_matrix *trans_matrix, t_tuple *tup);
/*
t_matrix	*matrix_matrix(int h, int w);
t_matrix	*matrix_identity(int range);
t_matrix	*tuple_to_matrix(t_tuple *t);
void		matrix_free(t_matrix *m);
t_matrix	*matrix_copy(t_matrix *m);

t_matrix	*matrix_multiply(t_matrix *m1, t_matrix *m2);
t_matrix	*matrix_transpose(t_matrix *m);
t_matrix	*matrix_sub(t_matrix *m, int column, int row);

double		matrix_minor(t_matrix *m, int from, int to);
double		matrix_cofactor(t_matrix *m, int from, int to);

t_matrix	*matrix_invert(t_matrix *m);

*/

void	matrix_translate(t_matrix *m, t_tuple *tpl);
void	matrix_scale(t_matrix *m, t_tuple *tpl);
/*
t_matrix	*matrix_translate(double x, double y, double z);
t_matrix	*matrix_scale(double x, double y, double z);

t_matrix	*view_transform(t_tuple *from, t_tuple *to, t_tuple *up);

t_matrix	*rotate_axis_angle(t_tuple *u, double angle);
t_matrix	*rotate_align(t_tuple *v1, t_tuple *v2);
*/
t_matrix	*matrix_x_rotate(double r);
t_matrix	*matrix_y_rotate(double r);
t_matrix	*matrix_z_rotate(double r);

void	rotate_axis_angle(t_matrix *ret, t_tuple *u, double angle);
void	rotate_align(t_matrix * res, t_tuple *v1, t_tuple *v2);

void	view_transform(t_matrix *view_mtx, t_tuple *from, t_tuple *to, t_tuple *up);

#endif //RT_CHALLENGE_MATRIX_H
