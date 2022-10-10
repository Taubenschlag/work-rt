/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 00:00:28 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_matrix	*invert(double determinant, t_matrix *m, t_matrix *inverted)
{
	int			i;
	int			j;
	t_matrix	*cofactors;
	double		diag;

	i = -1;
	cofactors = matrix_matrix(m->h, m->w);
	while (++i < m->h)
	{
		j = -1;
		while (++j < m->w)
			cofactors->matrix[i][j] = matrix_cofactor(m, i, j);
	}
	inverted = matrix_transpose(cofactors);
	i = -1;
	while (++i < m->h)
	{
		j = -1;
		while (++j < m->w)
		{
			diag = inverted->matrix[i][j] / determinant;
			inverted->matrix[i][j] = diag;
		}
	}
	return (inverted);
}

t_matrix	*matrix_invert(t_matrix *m)
{
	double		determinant;
	t_matrix	*inverted;

	inverted = NULL;
	determinant = matrix_determinant(m);
	if (determinant)
		inverted = invert(determinant, m, inverted);
	if (!inverted)
		return (NULL);
	return (inverted);
}

// TODO ternary
t_tuple	*tuple_apply_trans_matrix(t_matrix *trans_matrix, t_tuple *tup)
{
	t_matrix	*source_tuple_converted;
	t_matrix	*product;
	t_tuple		*res;
	int			need_free;

	source_tuple_converted = tuple_to_matrix(tup);
	if (trans_matrix)
		product = matrix_multiply(trans_matrix, source_tuple_converted);
	else
		product = source_tuple_converted;
	need_free = trans_matrix ? 0 : 1;
	res = tuple_point(
			product->matrix[0][0], product->matrix[1][0],
			product->matrix[2][0]);
	if (tuple_is_vector(tup))
		res->type = IS_VECTOR;
	if (trans_matrix)
		matrix_free(product);
	if (need_free)
	{
		matrix_free(trans_matrix);
		matrix_free(source_tuple_converted);
	}
	free(tup);
	return (res);
}

t_matrix	*vt_combine_matrix(t_tuple *left, t_tuple *true_up, t_tuple *forward)
{
	t_matrix	*res;

	res = matrix_identity(4);
	res->matrix[0][0] = left->x;
	res->matrix[0][1] = left->y;
	res->matrix[0][2] = left->z;
	res->matrix[1][0] = true_up->x;
	res->matrix[1][1] = true_up->y;
	res->matrix[1][2] = true_up->z;
	res->matrix[2][0] = -1 * forward->x;
	res->matrix[2][1] = -1 * forward->y;
	res->matrix[2][2] = -1 * forward->z;
	tuple_free(forward);
	tuple_free(left);
	tuple_free(true_up);
	return (res);
}

t_matrix	*view_transform(t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_tuple		*forward;
	t_tuple		*left;
	t_tuple		*tmp;
	t_matrix	*res;
	t_matrix	*view_matrix;

	tmp = tuple_substract(to, tuple_copy(from));
	forward = tuple_normalize(tmp);
	tmp = tuple_normalize(up);
	left = tuple_cross_product(forward, tmp);
	tuple_free(tmp);
	from = tuple_negate(from);
	res = vt_combine_matrix(left, tuple_cross_product(left, forward), forward);
	view_matrix = matrix_multiply(
			res, matrix_translate(from->x, from->y, from->z));
	tuple_free(from);
	return (view_matrix);
}
