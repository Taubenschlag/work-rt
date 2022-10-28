/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_advanced_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 02:08:55 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_tuple	*tuple_multiply(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*t;

	t = (t_tuple *)malloc(sizeof(t_tuple));
	t->x = t1->x * t2->x;
	t->y = t1->y * t2->y;
	t->z = t1->z * t2->z;
	t->type = t1->type * t2->type;
	return (t);
}

t_tuple	*tuple_reflect(t_tuple *v_in, t_tuple *v_normal)
{
	t_tuple	*v_out;
	t_tuple	*tmp;

	tmp = tuple_scalar_multiply(
			tuple_copy(v_normal), tuple_dot_product(v_in, v_normal) * 2);
	v_out = tuple_substract(v_in, tmp);
	return (v_out);
}

t_tuple	*tuple_color(double r, double g, double b)
{
	t_tuple	*t;

	t = (t_tuple *)malloc(sizeof(t_tuple));
	t->x = r;
	t->y = g;
	t->z = b;
	t->type = 2;
	return (t);
}

t_tuple	*tuple_copy(t_tuple *t)
{
	t_tuple	*res;

	res = tuple_point(t->x, t->y, t->z);
	res->type = t->type;
	return (res);
}
