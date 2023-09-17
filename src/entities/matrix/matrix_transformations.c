/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 19:47:34 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	matrix_translate(t_matrix *m, t_tuple *tpl)
{
	matrix_identity(m, M_MAX);
	m->mtx[0][3] = tpl->x;
	m->mtx[1][3] = tpl->y;
	m->mtx[2][3] = tpl->z;
}

void	matrix_scale(t_matrix *m, t_tuple *tpl)
{
	matrix_identity(m, M_MAX);
	m->mtx[0][0] = tpl->x;
	m->mtx[1][1] = tpl->y;
	m->mtx[2][2] = tpl->z;
}

/*
t_matrix	*matrix_x_rotate(double r)
{
	t_matrix	*scl;

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

t_matrix	*matrix_y_rotate(double r)
{
	t_matrix	*scl;

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

t_matrix	*matrix_z_rotate(double r)
{
	t_matrix	*scl;

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
*/