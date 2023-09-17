/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_advanced_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 19:58:13 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

int	tuple_is_vector(t_tuple *tuple)
{
	return (tuple->type == IS_VECTOR);
}

int	tuple_equals(t_tuple *t1, t_tuple *t2)
{
	int	res;

	res = 0;
	if (fabs(t1->x - t2->x) < DOUBLE_PREC)
	{
		if (fabs(t1->y - t2->y) < DOUBLE_PREC)
		{
			if (fabs(t1->z - t2->z) < DOUBLE_PREC)
				res = 1;
		}
	}
	return (res);
}

void	tuple_add(t_tuple *res, t_tuple *t1, t_tuple *t2)
{
	res->x = t1->x + t2->x;
	res->y = t1->y + t2->y;
	res->z = t1->z + t2->z;
	res->type = t1->type + t2->type;
}

void	tuple_substract(t_tuple *res, t_tuple *t1, t_tuple *t2)
{
	res->x = t1->x - t2->x;
	res->y = t1->y - t2->y;
	res->z = t1->z - t2->z;
	res->type = t1->type - t2->type;
}

void	tuple_scalar_multiply(t_tuple *res, t_tuple *t, double scale)
{
	res->x = t->x * scale;
	res->y = t->y * scale;
	res->z = t->z * scale;
	res->type = t->type;
}
