/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_2a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:56:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/16 18:06:37 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	cyl_int_cap(t_shape *s, t_ray *r, t_intersection_list **ret)
{
	double		t1;
	double		t2;
	t_cylinder	*cy;

	cy = (t_cylinder *)s->shape;
	if (!(cy->closed) || fabs(r->dir.y) < 0.0000001)
		return ;
	t1 = (cy->min - r->origin.y) / r->dir.y;
	if (check_cap(r, t1))
		add_intersection(intersect_make_shape(s, t1),
			ret);
	t2 = (cy->max - r->origin.y) / r->dir.y;
	if (check_cap(r, t2))
		add_intersection(intersect_make_shape(s, t2),
			ret);
}

void	cylinder_discriminant(t_cylinder *cy, t_ray *ray)
{
	cy->a = ray->dir.x * ray->dir.x
		+ ray->dir.z * ray->dir.z;
	cy->b = 2 * ray->dir.x * ray->origin.x
		+ 2 * ray->dir.z * ray->origin.z;
	cy->c = ray->origin.x * ray->origin.x
		+ ray->origin.z * ray->origin.z
		- 1;
	cy->disc = cy->b * cy->b - 4 * cy->a * cy->c;
}

void	cylinder_hit_truncate(t_shape *s, t_ray *ray, t_intersection_list **ret)
{
	t_cylinder	*cy;
	double		t1;
	double		t2;
	double		y1;
	double		y2;

	cy = (t_cylinder *)s->shape;
	t1 = (-1 * cy->b - sqrt(cy->disc)) / (2 * cy->a);
	t2 = (-1 * cy->b + sqrt(cy->disc)) / (2 * cy->a);
	y1 = ray->origin.y + dmin(t1, t2) * ray->dir.y;
	if ((cy)->min < y1 && y1 < (cy)->max)
		add_intersection(
			intersect_make_shape(s, dmin(t1, t2)),
			ret);
	y2 = ray->origin.y + dmax(t1, t2) * ray->dir.y;
	if ((cy)->min < y2 && y2 < (cy)->max)
		add_intersection(
			intersect_make_shape(s, dmax(t1, t2)),
			ret);
}

t_intersection_list	*intersection_ray_cylinder(t_shape *s, t_ray *ray)
{
	t_intersection_list	*ret;
	t_cylinder			*cy;

	cy = (t_cylinder *)s->shape;
	ret = intersection_list_make(0);
	cylinder_discriminant(cy, ray);
	if (fabs(cy->a) < 0.000001)
	{
		cyl_int_cap(s, ray, &ret);
		return (ret);
	}
	if (cy->disc < 0)
		return (ret);
	cylinder_hit_truncate(s, ray, &ret);
	cyl_int_cap(s, ray, &ret);
	return (ret);
}
