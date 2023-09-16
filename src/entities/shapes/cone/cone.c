/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/16 21:51:34 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

t_cone	*cone_cone(void)
{
	t_cone	*cone;

	cone = (t_cone *)malloc(sizeof(t_cone));
	cone->closed = 0;
	cone->min = INFINITY * -1;
	cone->max = INFINITY * 1;
	return (cone);
}

void	cone_normale_at(t_tuple *res, t_tuple *t, t_cone *c)
{
	double	dist;
	double	y;

	dist = sqrt(t->x * t->x + t->z * t-> z);
	if (dist <= fabs(c->max) && t->y >= (c->max - 0.00001))
	{
		tuple_vector(res, 0, 1, 0);
		return ;
	}
	if (dist <= fabs(c->min) && t->y <= (c->min + 0.00001))
	{
		tuple_vector(res, 0, -1, 0);
		return ;
	}
	y = sqrt(t->x * t->x + t->z * t-> z);
	if (t-> y > 0)
		y = y * -1;
	tuple_vector(res, t->x, y, t->z);
}

/*
t_tuple	*cone_normale_at(t_tuple *t, t_cone *c)
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
*/

int	check_cap_cone_max(t_ray *r, double t, double max)
{
	double	x;
	double	y;
	double	temp;

	x = r->origin.x + t * r->dir.x;
	y = r->origin.z + t * r->dir.z;
	temp = fabs(x * x) + fabs(y * y);
	return (temp <= max);
}

int	check_cap_cone_min(t_ray *r, double t, double min)
{
	double	x;
	double	y;
	double	temp;

	x = r->origin.x + t * r->dir.x;
	y = r->origin.z + t * r->dir.z;
	temp = fabs(x * x) + fabs(y * y);
	return (temp <= min);
}

t_cone	*cone_param(double h)
{
	t_cone	*c;

	c = cone_cone();
	c->min = h * -1;
	c->max = 0;
	c->closed = 1;
	return (c);
}
