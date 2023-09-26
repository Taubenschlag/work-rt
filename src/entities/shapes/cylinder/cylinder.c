/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/26 19:35:52 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

t_cylinder	*cylinder_cylinder(void)
{
	t_cylinder	*c;

	c = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (c == NULL)
		return (NULL);
	c->closed = 0;
	c->min = INFINITY * -1;
	c->max = INFINITY * 1;
	return (c);
}

t_cylinder	*cylinder_params(double h)
{
	t_cylinder	*c;

	c = cylinder_cylinder();
	c->min = 0;
	c->max = h;
	c->closed = 1;
	return (c);
}

void	cylinder_normale_at(t_tuple *res, t_tuple *t, t_cylinder *c)
{
	double	dist;

	dist = t->x * t->x + t->z * t->z;
	if (dist < 1 && t->y >= (c->max - 0.00001))
	{
		tuple_vector(res, 0, 1, 0);
		return ;
	}
	if (dist < 1 && t->y <= (c->min + 0.00001))
	{
		tuple_vector(res, 0, -1, 0);
		return ;
	}
	tuple_vector(res, t->x, 0, t->z);
}

int	check_cap(t_ray *r, double t)
{
	double	x;
	double	z;
	double	temp;

	x = r->origin.x + t * r->dir.x;
	z = r->origin.z + t * r->dir.z;
	temp = fabs(x * x) + fabs(z * z);
	return (temp <= 1);
}

void	cylinder_free(t_cylinder *c)
{
	free(c);
}
