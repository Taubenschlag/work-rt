/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 23:43:25 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_matrix	*matrix_matrix(int h, int w)
{
	t_matrix	*m;
	int			i;
	int			j;

	i = 0;
	m = (t_matrix *)malloc(sizeof(t_matrix));
	m->w = w;
	m->h = h;
	m->matrix = (double **)malloc(sizeof(double *) * h);
	while (i < h)
	{
		m->matrix[i] = (double *)malloc(sizeof(double) * w);
		j = 0;
		while (j < w)
		{
			m->matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	return (m);
}

t_matrix	*matrix_identity(int range)
{
	t_matrix	*m;
	int			i;

	i = 0;
	m = matrix_matrix(range, range);
	while (i < range)
	{
		m->matrix[i][i] = 1;
		i++;
	}
	return (m);
}

int	matrix_equals(t_matrix *m1, t_matrix *m2)
{
	int	i;
	int	j;

	if (m1->w == m2->w && m1->h == m2->h)
	{
		i = 0;
		while (i < m1->h)
		{
			j = 0;
			while (j < m1->w)
			{
				if (fabs(m1->matrix[i][j] - m2->matrix[i][j]) > DOUBLE_PREC)
					return (0);
				j++;
			}
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	matrix_free(t_matrix *m)
{
	int	i;

	if (m)
	{
		i = 0;
		while (i < m->h)
		{
			free((m->matrix)[i]);
			i++;
		}
		free(m->matrix);
		free(m);
	}
}

t_matrix	*tuple_to_matrix(t_tuple *t)
{
	t_matrix	*m;

	m = matrix_matrix(4, 1);
	m->matrix[0][0] = t->x;
	m->matrix[1][0] = t->y;
	m->matrix[2][0] = t->z;
	m->matrix[3][0] = (double)t->type;
	return (m);
}
