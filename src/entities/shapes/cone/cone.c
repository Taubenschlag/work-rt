/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/26 19:35:02 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

t_cone	*cone_cone(void)
{
	t_cone	*cone;

	cone = (t_cone *)malloc(sizeof(t_cone));
	if (cone == NULL)
		return (NULL);
	cone->min = INFINITY * -1;
	cone->max = INFINITY;
	return (cone);
}

t_cone	*cone_param(double h)
{
	t_cone	*c;

	c = cone_cone();
	c->min = h * -1;
	c->max = 0;
	return (c);
}

void	cone_normale_at(t_tuple *res, t_tuple *t, t_cone *c)
{
	double	dist;
	double	y;

	dist = t->x * t->x + t->z * t-> z;
	if (dist <= (fabs(c->min) * 2) && t->y <= (c->min + 0.00001))
	{
		tuple_vector(res, 0, -1, 0);
		return ;
	}
	y = sqrt(t->x * t->x + t->z * t-> z);
	if (t->y > 0)
		y = y * -1;
	tuple_vector(res, t->x, y, t->z);
}

int	check_cap_cone_min(t_ray *r, double t, double min)
{
	double	x;
	double	z;
	double	temp;

	x = r->origin.x + t * r->dir.x;
	z = r->origin.z + t * r->dir.z;
	min *= min;
	temp = fabs(x * x) + fabs(z * z);
	return (temp <= min);
}
