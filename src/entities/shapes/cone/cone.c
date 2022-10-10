/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 21:58:41 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

s_cone	*cone_cone(void)
{
	s_cone	*cone;

	cone = (s_cone *)malloc(sizeof(s_cone));
	cone->closed = 0;
	cone->min = INFINITY * -1;
	cone->max = INFINITY * 1;
	return (cone);
}

s_tuple	*cone_normale_at(s_tuple *t, s_cone *c)
{
	double	dist;
	double	y;

	dist = sqrt(t->x * t->x + t->z * t-> z);
	if (dist <= fabs(c->max) && t->y >= (c->max - 0.00001))
		return (tuple_vector(0, 1, 0));
	if (dist <= fabs(c->min) && t->y <= (c->min + 0.00001))
		return (tuple_vector(0, -1, 0));
	y = sqrt(t->x * t->x + t->z * t-> z);
	if (t-> y > 0)
		y = y * -1;
	return (tuple_vector(t->x, y, t->z));
}

int	check_cap_cone_max(s_ray *r, double t, double max)
{
	double	x;
	double	y;
	double	temp;

	x = r->origin->x + t * r->dir->x;
	y = r->origin->z + t * r->dir->z;
	temp = fabs(x * x) + fabs(y * y);
	return (temp <= max);
}

int	check_cap_cone_min(s_ray *r, double t, double min)
{
	double	x;
	double	y;
	double	temp;

	x = r->origin->x + t * r->dir->x;
	y = r->origin->z + t * r->dir->z;
	temp = fabs(x * x) + fabs(y * y);
	return (temp <= min);
}

s_cone	*cone_param(double h)
{
	s_cone	*c;

	c = cone_cone();
	c->min = h * -1;
	c->max = 0;
	c->closed = 1;
	return (c);
}
