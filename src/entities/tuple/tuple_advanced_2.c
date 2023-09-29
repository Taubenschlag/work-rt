/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_advanced_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/29 20:12:31 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	tuple_negate(t_tuple *res, t_tuple *t)
{
	res->x = t->x * -1;
	res->y = t->y * -1;
	res->z = t->z * -1;
	res->type = t->type * -1;
}

double	tuple_length(t_tuple *t)
{
	return (
		sqrt(
			t->x * t->x
			+ t->y * t->y
			+ t->z * t->z
			+ t->type * t->type)
	);
}

void	tuple_normalize(t_tuple *res, t_tuple *t)
{
	double	length;

	length = tuple_length(t);
	tuple_vector(res, t->x / length, t->y / length, t->z / length);
}

double	tuple_dot_product(t_tuple *t1, t_tuple *t2)
{
	return (
		t1->x * t2->x
		+ t1->y * t2->y
		+ t1->z * t2->z
	);
}

void	tuple_cross_product(t_tuple *res, t_tuple *t1, t_tuple *t2)
{
	tuple_vector(res, t1->y * t2->z - t1->z * t2->y, \
					t1->z * t2->x - t1->x * t2->z, \
					t1->x * t2->y - t1->y * t2->x);
}
