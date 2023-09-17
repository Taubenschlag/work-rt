/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 21:46:20 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

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
*/
//t_matrix	*matrix_multiply(t_matrix *res, t_matrix *m1, t_matrix *m2)
void	matrix_multiply(t_matrix *res, t_matrix *m1, t_matrix *m2)
{
	int			it[3];
	double		tmp;

	matrix_matrix(res, min(m1->h, m2->h), min(m1->w, m2->w));
	/* DEBUG 
	printf("mtx_multiply\n");
	printf("\t m1->h:[%d],  m1->w:[%d]\n", m1->h, m1->w);
	printf("\t m2->h:[%d],  m2->w:[%d]\n", m2->h, m2->w);
	printf("\tres->h:[%d], res->w:[%d]\n", res->h, res->w);
	//exit(0);
	printf("mtx m1:\n");
	print_matrix(m1);
	printf("mtx m2:\n");
	print_matrix(m2);
	*/
	it[0] = -1;
	while (++it[0] < res->h)
	{
		// DEBUG 
		//printf(" [");
		//
		it[1] = -1;
		while (++it[1] < res->w)
		{
			it[2] = 0;
			tmp = 0;
			while (it[2] < m1->w && it[2] < m2->h)
			{
				tmp += m1->mtx[it[0]][it[2]] * m2->mtx[it[2]][it[1]];
				// DEBUG 
				//printf("\ttmp:[%.1f]\tm1[%d][%d]: [%.1f]\tm2[%d][%d]: [%.1f]\n", tmp, it[0], it[2], m1->matrix[it[0]][it[1]], it[2], it[1], m1->matrix[it[2]][it[1]]);
				//
				it[2]++;
			}
			res->mtx[it[0]][it[1]] = tmp;
		}
	}
	/* DEBUG
	printf("mtx res:\n");
	print_matrix(res);
	*/
}

void	matrix_transpose(t_matrix *res, t_matrix *m)
{
	int			i;
	int			j;

	matrix_matrix(res, m->h, m->w);
	i = 0;
	while (i < res->h)
	{
		j = 0;
		while (j < res->w)
		{
			res->mtx[i][j] = m->mtx[j][i];
			j++;
		}
		i++;
	}
}

double	matrix_determinant(t_matrix *m)
{
	int		column;
	double	determinant;
	t_matrix	sub;

	determinant = 0;
	column = -1;
	if (m->h == 2 && m->w == 2)
		determinant = m->mtx[0][0] * m->mtx[1][1]
			- m->mtx[0][1] * m->mtx[1][0];
	else
		while (++column < m->w)
			determinant += m->mtx[0][column]
				* matrix_cofactor(&sub, m, 0, column);
	return (determinant);
}

void	matrix_sub(t_matrix *res, t_matrix *m, int column, int row)
{
	int			i;
	int			j;
	int			i_skip;
	int			j_skip;

	matrix_matrix(res, m->h - 1, m->w - 1);
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
			res->mtx[i - i_skip][j - j_skip] = m->mtx[i][j];
			j++;
		}
		i++;
	}
}

void	matrix_copy(t_matrix *ret, t_matrix *m)
{
	int			i;
	int			j;

	matrix_matrix(ret, m->h, m->w);
	i = -1;
	while (++i < ret->h)
	{
		j = -1;
		while (++j < ret->w)
			ret->mtx[i][j] = m->mtx[i][j];
	}
}
