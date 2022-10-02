/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 03:12:54 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

s_cylinder	*cylinder_cylinder(void)
{
	s_cylinder	*c;

	c = (s_cylinder *)malloc(sizeof(s_cylinder));
	c->closed = 0;
	c->min = INFINITY * -1;
	c->max = INFINITY * 1;
	return (c);
}

s_cylinder	*cylinder_params(double h)
{
	s_cylinder	*c;

	c = cylinder_cylinder();
	c->min = 0;
	c->max = h;
	c->closed = 1;
	return (c);
}

s_tuple	*cylinder_normale_at(s_tuple *t, s_cylinder *c)
{
	double	dist;

	dist = t->x * t->x + t->z * t->z;
	if (dist < 1 && t->y >= (c->max - 0.00001))
		return (tuple_vector(0, 1, 0));
	if (dist < 1 && t->y <= (c->min + 0.00001))
		return (tuple_vector(0, -1, 0));
	return (tuple_vector(t->x, 0, t->z));
}

int	check_cap(s_ray *r, double t)
{
	double	x;
	double	y;

	x = r->origin->x + t * r->dir->x;
	y = r->origin->z + t * r->dir->z;
	return ((x * x + y * y) <= 1);
}

void	cylinder_free(s_cylinder *c)
{
	free(c);
}
