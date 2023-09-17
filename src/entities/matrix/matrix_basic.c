/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 21:45:09 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

/* DEBUG */
void	print_matrix(t_matrix *m)
{
	int	h = 0;
	int	w = 0;

	/* DEBUG */
	printf("\tm->h: [%d], m->w: [%d]\n", m->h, m->w);
	/* ***** */
	while (h < m->h)
	{
		printf("\t[ ");
		w = 0;
		while (w < m->w)
		{
			printf("%.2f", m->mtx[h][w]);
			if (m->w > 1)
				printf("\t");
			w++;
		}
		printf("\t]\n");
		h++;
	}
	printf("\n");
}
/* ***** */

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
