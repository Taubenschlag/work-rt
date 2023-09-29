/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/29 20:07:49 by sbocanci         ###   ########.fr       */
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

void	tuple_apply_trans_matrix(t_tuple *res, t_matrix *trans_matrix, \
								t_tuple *tup)
{
	t_matrix	source_tuple_converted;
	t_matrix	prod;

	tuple_to_matrix(&source_tuple_converted, tup);
	if (trans_matrix)
	{
		matrix_multiply(&prod, trans_matrix, &source_tuple_converted);
		tuple_point(res, prod.mtx[0][0], prod.mtx[1][0], prod.mtx[2][0]);
	}
	else
	{
		prod = source_tuple_converted;
		tuple_point(res, source_tuple_converted.mtx[0][0], \
					source_tuple_converted.mtx[1][0], \
					source_tuple_converted.mtx[2][0]);
	}
	if (tuple_is_vector(tup))
		res->type = IS_VECTOR;
}

void	vt_combine_matrix(t_matrix *res, t_tuple *left, \
							t_tuple *true_up, t_tuple *forward)
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

void	view_transform(t_matrix *view_mtx, t_tuple *from, \
						t_tuple *to, t_tuple *up)
{
	t_tmp_m	tmp;
	t_tuple	forward;
	t_tuple	left;
	t_tuple	t_tmp;
	t_tuple	cros;

	tuple_substract(&t_tmp, to, from);
	tuple_normalize(&forward, &t_tmp);
	tuple_normalize(&t_tmp, up);
	tuple_cross_product(&left, &forward, &t_tmp);
	tuple_negate(&t_tmp, from);
	tuple_cross_product(&cros, &left, &forward);
	vt_combine_matrix(&tmp.sub, &left, &cros, &forward);
	matrix_translate(&tmp.transposed, &t_tmp);
	matrix_multiply(view_mtx, &tmp.sub, &tmp.transposed);
}
