/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/07 14:09:45 by sbocanci         ###   ########.fr       */
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
			printf("%.1f ", m->matrix[h][w]);
			w++;
		}
		printf("\t]\n");
		h++;
	}
	printf("\n");
}
/* ***** */
/*
t_matrix	*matrix_multiply(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*res;
	register int		it[3];
	register double		tmp;

	res = matrix_matrix(min(m1->h, m2->h), min(m1->w, m2->w));

	it[0] = -1;
	while (++it[0] < res->h)
	{
		it[1] = -1;
		while (++it[1] < res->w)
		{
			it[2] = 0;
			tmp = 0;
			while (it[2] < m1->w && it[2] < m2->h)
			{
				tmp += m1->matrix[it[0]][it[2]] * m2->matrix[it[2]][it[1]];
				it[2]++;
			}
			res->matrix[it[0]][it[1]] = tmp;
		}
	}
	matrix_free(m1);
	matrix_free(m2);
	return (res);
}
*/
/*
** Consider this input file with only one sphere to render:
** R 400 400
** A 0.6						255,255,255
** c	0,5,-8		0,0,1		0,1,0		70
** l	-10,10,-10	0.8			255,255,255	
** sp	0,5,0		5.0			225,25,25*
**
** So, it takes around 18 seconds to render just one sphere and use 
** DEBUG printfs in the function bellow
** ..around 7 seconds to render same setting but without printf DEBUG statements
**
** call from handle_sphere() receive:	m1[4][4] and m2[4][1] so the result is res[4][1]
** call from handle_plane() receive:	m1[4][4] and m2[4][1] so the result is res[4][1]
** call from handle_square() receive:	m1[4][4] and m2[4][1] so the result is res[4][1]
** call from handle_cylinder() receive:	m1[4][4] and m2[4][1] so the result is res[4][1]
** call from handle_triangle() receive:	m1[4][4] and m2[4][1] so the result is res[4][1]
** call from handle_cone() receive:		m1[4][4] and m2[4][1] so the result is res[4][1]
** call from handle_cube() receive:		m1[4][4] and m2[4][1] so the result is res[4][1]
**
*/
t_matrix	*matrix_multiply(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*res;
	int			it[3];
	double		tmp;

	res = matrix_matrix(min(m1->h, m2->h), min(m1->w, m2->w));

	printf("mtx_multiply\n");
	printf("\t m1->h:[%d],  m1->w:[%d]\n", m1->h, m1->w);
	printf("\t m2->h:[%d],  m2->w:[%d]\n", m2->h, m2->w);
	printf("\tres->h:[%d], res->w:[%d]\n", res->h, res->w);
	/* DEBUG */
	printf("mtx m1:\n");
	print_matrix(m1);
	printf("mtx m2:\n");
	print_matrix(m2);
	/* ***** */
	it[0] = -1;
	while (++it[0] < res->h)
	{
		/* DEBUG */
		//printf(" [");
		/* ***** */
		it[1] = -1;
		while (++it[1] < res->w)
		{
			it[2] = 0;
			tmp = 0;
			while (it[2] < m1->w && it[2] < m2->h)
			{
				tmp += m1->matrix[it[0]][it[2]] * m2->matrix[it[2]][it[1]];
				/* DEBUG */
				//printf("\ttmp:[%.1f]\tm1[%d][%d]: [%.1f]\tm2[%d][%d]: [%.1f]\n", tmp, it[0], it[2], m1->matrix[it[0]][it[1]], it[2], it[1], m1->matrix[it[2]][it[1]]);
				/* ***** */
				it[2]++;
			}
			res->matrix[it[0]][it[1]] = tmp;
		}
	}
	/* DEBUG */
	printf("mtx res:\n");
	print_matrix(res);
	/* ***** */
	matrix_free(m1);
	matrix_free(m2);
	return (res);
}

t_matrix	*matrix_transpose(t_matrix *m)
{
	t_matrix	*res;
	int			i;
	int			j;

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

double	matrix_determinant(t_matrix *m)
{
	int		column;
	double	determinant;

	determinant = 0;
	column = -1;
	if (m->h == 2 && m->w == 2)
		determinant = m->matrix[0][0] * m->matrix[1][1]
			- m->matrix[0][1] * m->matrix[1][0];
	else
		while (++column < m->w)
			determinant += m->matrix[0][column]
				* matrix_cofactor(m, 0, column);
	return (determinant);
}

t_matrix	*matrix_sub(t_matrix *m, int column, int row)
{
	t_matrix	*res;
	int			i;
	int			j;
	int			i_skip;
	int			j_skip;

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

t_matrix	*matrix_copy(t_matrix *m)
{
	t_matrix	*ret;
	int			i;
	int			j;

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
