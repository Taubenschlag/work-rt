/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_2a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:56:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/21 22:56:24 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_intersection_list	*cyl_int_cap(t_shape *c, t_ray *r, t_intersection_list *l)
{
	double	t;

	if (!(((t_cylinder *)c->shape)->closed) || fabs(r->dir->y) < 0.00001)
		return (l);
	t = (((t_cylinder *)c->shape)->min - r->origin->y) / r->dir->y;
	if (check_cap(r, t))
		add_intersection(intersect_make_shape(c, t), &l);
	t = (((t_cylinder *)c->shape)->max - r->origin->y) / r->dir->y;
	if (check_cap(r, t))
		add_intersection(intersect_make_shape(c, t), &l);
	return (l);
}

t_intersection_list	*intersection_ray_cylinder(t_shape *s, t_ray *ray)
{
	double				a;
	double				b;
	double				disc;
	double				t[2];
	t_intersection_list	*ret;

	a = ray->dir->x * ray->dir->x + ray->dir->z * ray->dir->z;
	ret = intersection_list_make(0);
	if (fabs(a) < 0.000001)
		return (cyl_int_cap(s, ray, ret));
	b = 2 * ray->dir->x * ray->origin->x + 2 * ray->dir->z * ray->origin->z;
	disc = b * b - 4 * a * (ray->origin->x * ray->origin->x
							+ ray->origin->z * ray->origin->z - 1);
	if (disc < 0)
		return (ret);
	t[0] = (-1 * b - sqrt(disc)) / (2 * a);
	t[1] = (-1 * b + sqrt(disc)) / (2 * a);
	a = ray->origin->y + mins(t, 2) * ray->dir->y;
	if (((t_cylinder *)s->shape)->min < a && a < ((t_cylinder *)s->shape)->max)
		add_intersection(intersect_make_shape(s, mins(t, 2)), &ret);
	a = ray->origin->y + maxs(t, 2) * ray->dir->y;
	if (((t_cylinder *)s->shape)->min < a && a < ((t_cylinder *)s->shape)->max)
		add_intersection(intersect_make_shape(s, maxs(t, 2)), &ret);
	return (cyl_int_cap(s, ray, ret));
}
