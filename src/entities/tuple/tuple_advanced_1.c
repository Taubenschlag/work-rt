/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_advanced_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 01:48:42 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

int	tuple_equals(s_tuple *t1, s_tuple *t2)
{
	int	res;

	res = 0;
	if (fabs(t1->x - t2->x) < DOUBLE_PREC)
		if (fabs(t1->y - t2->y) < DOUBLE_PREC)
			if (fabs(t1->z - t2->z) < DOUBLE_PREC)
				res = 1;
	tuple_free(t1);
	tuple_free(t2);
	return (res);
}

s_tuple	*tuple_add(s_tuple *t1, s_tuple *t2)
{
	s_tuple	*t;

	t = (s_tuple *)malloc(sizeof(s_tuple));
	t->x = t1->x + t2->x;
	t->y = t1->y + t2->y;
	t->z = t1->z + t2->z;
	t->type = t1->type + t2->type;
	tuple_free(t1);
	tuple_free(t2);
	return (t);
}

s_tuple	*tuple_substract(s_tuple *t1, s_tuple *t2)
{
	s_tuple	*t;

	t = (s_tuple *)malloc(sizeof(s_tuple));
	t->x = t1->x - t2->x;
	t->y = t1->y - t2->y;
	t->z = t1->z - t2->z;
	t->type = t1->type - t2->type;
	tuple_free(t1);
	tuple_free(t2);
	return (t);
}

s_tuple	*tuple_scalar_multiply(s_tuple *t, double scale)
{
	s_tuple	*res;

	res = (s_tuple *)malloc(sizeof(s_tuple));
	res->x = t->x * scale;
	res->y = t->y * scale;
	res->z = t->z * scale;
	res->type = t->type;
	tuple_free(t);
	return (res);
}
