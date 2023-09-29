/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/29 19:59:40 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	rotate_axis_angle(t_matrix *ret, t_tuple *u, double angle)
{
	double		sin_a;
	double		cos_a;
	double		one_min_cos_a;

	sin_a = sin(angle);
	cos_a = cos(angle);
	one_min_cos_a = 1 - cos_a;
	matrix_identity(ret, 4);
	ret->mtx[0][0] = (u->x * u->x * one_min_cos_a) + cos_a;
	ret->mtx[0][1] = (u->y * u->x * one_min_cos_a) - (sin_a * u->z);
	ret->mtx[0][2] = (u->z * u->x * one_min_cos_a) + (sin_a * u->y);
	ret->mtx[1][0] = (u->x * u->y * one_min_cos_a) + (sin_a * u->z);
	ret->mtx[1][1] = (u->y * u->y * one_min_cos_a) + cos_a;
	ret->mtx[1][2] = (u->z * u->y * one_min_cos_a) - (sin_a * u->x);
	ret->mtx[2][0] = (u->x * u->z * one_min_cos_a) - (sin_a * u->y);
	ret->mtx[2][1] = (u->y * u->z * one_min_cos_a) + (sin_a * u->x);
	ret->mtx[2][2] = (u->z * u->z * one_min_cos_a) + cos_a;
}

void	rotate_align(t_matrix *res, t_tuple *v1, t_tuple *v2)
{
	t_tuple		axis;
	t_tuple		tmp;
	double		dot;
	double		angle;

	tuple_cross_product(&tmp, v1, v2);
	tuple_normalize(&axis, &tmp);
	dot = tuple_dot_product(v1, v2);
	angle = acos(dot);
	rotate_axis_angle(res, &axis, angle);
}

double	matrix_minor(t_matrix *sub, t_matrix *m, int from, int to)
{
	double		res;

	matrix_sub(sub, m, from, to);
	res = matrix_determinant(sub);
	return (res);
}

double	matrix_cofactor(t_matrix *sub, t_matrix *m, int from, int to)
{
	double	minor;

	minor = matrix_minor(sub, m, from, to);
	if ((from + to) % 2)
		return (minor * -1);
	return (minor);
}
