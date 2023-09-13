/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/13 17:58:38 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	matrix_matrix(t_matrix *m, int h, int w)
{
	int			i;
	int			j;

	i = 0;
	m->w = w;
	m->h = h;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			m->mtx[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	matrix_identity(t_matrix *m, int range)
{
	int			i;

	i = 0;
	matrix_matrix(m, range, range);
	while (i < range)
	{
		m->mtx[i][i] = 1;
		i++;
	}
}

void	tuple_to_matrix(t_matrix *m, t_tuple *t)
{
	matrix_matrix(m, 4, 1);
	m->mtx[0][0] = t->x;
	m->mtx[1][0] = t->y;
	m->mtx[2][0] = t->z;
	m->mtx[3][0] = (double)t->type;
	m->h = 4;
	m->w = 1;
}

/*
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

void	matrix_matrix(t_matrix *m, int h, int w)
{
	int			i;
	int			j;

	m->w = w;
	m->h = h;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			m->mtx[i][j] = 0;
			j++;
		}
		i++;
	}
}
*/
