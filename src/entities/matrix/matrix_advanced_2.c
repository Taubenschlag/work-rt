/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/11 14:44:15 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

//t_matrix	*invert(double determinant, t_matrix *m, t_matrix *inverted)
void	invert(t_matrix *cofactors, double determinant, t_matrix *m, t_matrix *inverted)
{
	int			i;
	int			j;
	//t_matrix	*cofactors;
	double		diag;
	t_matrix	sub;

	i = -1;
	//cofactors = matrix_matrix(m->h, m->w);
	matrix_matrix(cofactors, m->h, m->w);
	while (++i < m->h)
	{
		j = -1;
		while (++j < m->w)
			cofactors->mtx[i][j] = matrix_cofactor(&sub, m, i, j);
			//cofactors->mtx[i][j] = matrix_cofactor(m, i, j);
	}
	//inverted = matrix_transpose(cofactors);
	matrix_transpose(inverted, cofactors);
	i = -1;
	while (++i < m->h)
	{
		j = -1;
		while (++j < m->w)
		{
			diag = inverted->mtx[i][j] / determinant;
			inverted->mtx[i][j] = diag;
		}
	}
	//return (inverted);
}

//t_matrix	*matrix_invert(t_matrix *m)
void	matrix_invert(t_matrix *inverted, t_matrix *m)
{
	double		determinant;
	//t_matrix	*inverted;

	//inverted = NULL;
	determinant = matrix_determinant(m);
	if (determinant)
		invert(inverted, determinant, m, inverted);
	/*
		inverted = invert(determinant, m, inverted);
	if (!inverted)
		return (NULL);
	return (inverted);
	*/
}

//void	tuple_apply_trans_matrix(t_tuple *res, t_matrix *trans_matrix, t_tuple *tup)
t_tuple	*tuple_apply_trans_matrix(t_matrix *trans_matrix, t_tuple *tup)
{
	t_matrix	source_tuple_converted;
	t_matrix	product;
	t_tuple		*res;
	//int			need_free;

	/* DEBUG */
	printf("tuple_apply_trans_matrix\n");
	/* ***** */
	tuple_to_matrix(&source_tuple_converted, tup);
	//source_tuple_converted = tuple_to_matrix(tup);
	//need_free = 1;
	if (trans_matrix)
	{
		matrix_multiply(&product, trans_matrix, &source_tuple_converted);
		//product = matrix_multiply(trans_matrix, source_tuple_converted);
		//need_free = 0;
		res = tuple_point(product.mtx[0][0], 
			product.mtx[1][0], product.mtx[2][0]);
	}
	else
	{
		product = source_tuple_converted;
		res = tuple_point(source_tuple_converted.mtx[0][0], 
					source_tuple_converted.mtx[1][0], 
					source_tuple_converted.mtx[2][0]);
	}
	if (tuple_is_vector(tup))
		res->type = IS_VECTOR;
	/*
	if (need_free)
		matrix_free(trans_matrix);
	matrix_free(product);
	*/
	free(tup);
	return (res);
}

//t_matrix	*vt_combine_matrix(t_tuple *left, t_tuple *true_up, t_tuple *forward)
void	vt_combine_matrix(t_matrix *res, t_tuple *left, t_tuple *true_up, t_tuple *forward)
{
	//t_matrix	*res;

	//res = matrix_identity(4);
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
	tuple_free(forward);
	tuple_free(left);
	tuple_free(true_up);
	//return (res);
}

//t_matrix	*view_transform(t_tuple *from, t_tuple *to, t_tuple *up);
void	view_transform(t_matrix *view_mtx, t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_tuple		*forward;
	t_tuple		*left;
	t_tuple		*tmp;
	t_matrix	res;
	t_matrix	tmp_m;
	//t_matrix	*view_matrix;

	tmp = tuple_substract(to, tuple_copy(from));
	forward = tuple_normalize(tmp);
	tmp = tuple_normalize(up);
	left = tuple_cross_product(forward, tmp);
	tuple_free(tmp);
	from = tuple_negate(from);
	//res = vt_combine_matrix(left, tuple_cross_product(left, forward), forward);
	vt_combine_matrix(&res, left, tuple_cross_product(left, forward), forward);
	//view_matrix = matrix_multiply(res, matrix_translate(from->x, from->y, from->z));
	matrix_translate(&tmp_m, from);
	matrix_multiply(view_mtx, &res, &tmp_m);
	tuple_free(from);
	//return (view_matrix);
}
