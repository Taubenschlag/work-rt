/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/18 00:19:17 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_matrix	*rotate_axis_angle(t_tuple *u, double angle)
{
	double		sin_a;
	double		cos_a;
	double		one_min_cos_a;
	t_matrix	*ret;

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

t_matrix	*rotate_align(t_tuple *v1, t_tuple *v2)
{
	t_tuple		*axis;
	double		dot;
	double		angle;
	t_matrix	*res;

	axis = tuple_normalize(tuple_cross_product(v1, v2));
	dot = tuple_dot_product(v1, v2);
	angle = acos(dot);
	res = rotate_axis_angle(axis, angle);
	tuple_free(v1);
	tuple_free(axis);
	return (res);
}

double	matrix_minor(t_matrix *m, int from, int to)
{
	t_matrix	*sub;
	double		res;

	sub = matrix_sub(m, from, to);
	res = matrix_determinant(sub);
	matrix_free(sub);
	return (res);
}

// changed
double	matrix_cofactor(t_matrix *m, int from, int to)
{
	double	minor;

	minor = matrix_minor(m, from, to);
	if ((from + to) % 2)
		return (minor * -1);
	return (minor);
}
