/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/19 17:07:32 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	invert(t_tmp_m *m_tmp, t_matrix *m)
{
	int			i;
	int			j;
	double		diag;

	i = -1;
	matrix_matrix(&m_tmp->co_f, m->h, m->w);
	while (++i < m->h)
	{
		j = -1;
		while (++j < m->w)
			m_tmp->co_f.mtx[i][j] = matrix_cofactor(&m_tmp->sub, m, i, j);
	}
	matrix_transpose(&m_tmp->inv, &m_tmp->co_f);
	i = -1;
	while (++i < m->h)
	{
		j = -1;
		while (++j < m->w)
		{
			diag = m_tmp->inv.mtx[i][j] / m_tmp->determinant;
			m_tmp->inv.mtx[i][j] = diag;
		}
	}
}

void	matrix_invert(t_tmp_m *m_tmp, t_matrix *m)
{
	m_tmp->determinant = matrix_determinant(m);
	if (m_tmp->determinant)
		invert(m_tmp, m);
}

void	tuple_apply_trans_matrix(t_tuple *res, t_matrix *trans_matrix, t_tuple *tup)
{
	t_matrix	source_tuple_converted;
	t_matrix	product;

	/* DEBUG 
	printf("tuple_apply_trans_matrix\n");
	print_matrix(trans_matrix);
	printf("tup:\t");
	print_tuple(tup);
*/
	/* ***** */
	tuple_to_matrix(&source_tuple_converted, tup);
	if (trans_matrix)
	{
		matrix_multiply(&product, trans_matrix, &source_tuple_converted);
		tuple_point(res, product.mtx[0][0], product.mtx[1][0], product.mtx[2][0]);
	}
	else
	{
		product = source_tuple_converted;
		tuple_point(res, source_tuple_converted.mtx[0][0], 
					source_tuple_converted.mtx[1][0], 
					source_tuple_converted.mtx[2][0]);
	}
	if (tuple_is_vector(tup))
		res->type = IS_VECTOR;
}

void	vt_combine_matrix(t_matrix *res, t_tuple *left, t_tuple *true_up, t_tuple *forward)
{
	matrix_identity(res, 4);
	res->mtx[0][0] = left->x;
	res->mtx[0][1] = left->y;
	res->mtx[0][2] = left->z;
	res->mtx[1][0] = true_up->x;
	res->mtx[1][1] = true_up->y;
	res->mtx[1][2] = true_up->z;
	res->mtx[2][0] = -1 * forward->x;
	res->mtx[2][1] = -1 * forward->y;
	res->mtx[2][2] = -1 * forward->z;
}

void	view_transform(t_matrix *view_mtx, t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		tmp;
	t_tuple		cros;
	t_matrix	res;
	t_matrix	tmp_m;

	tuple_substract(&tmp, to, from);
	tuple_normalize(&forward, &tmp);
	tuple_normalize(&tmp, up);
	tuple_cross_product(&left, &forward, &tmp);
	tuple_negate(&tmp, from);
	tuple_cross_product(&cros, &left, &forward);
	vt_combine_matrix(&res, &left, &cros, &forward);
	matrix_translate(&tmp_m, &tmp);
	matrix_multiply(view_mtx, &res, &tmp_m);
}
