/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/21 18:28:26 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	co_intrs_cap(t_shape *s, t_ray *r, t_intersection_list **ret)
{
	double	t1;
	double	t2;
	t_cone	*co;

	co = (t_cone *)s->shape;
	if (!(co->closed) || fabs(r->dir.y) < 0.0000001)
		return ;
	t1 = (co->min - r->origin.y) / r->dir.y;
	if (check_cap_cone_min(r, t1, co->min))
		add_intersection(intersect_make_shape(s, t1),
			ret);
	t2 = (co->max - r->origin.y) / r->dir.y;
	if (check_cap_cone_max(r, t2, co->max))
		add_intersection(intersect_make_shape(s, t2),
			ret);
}

/* PAGE 189 TRTC */
void	cone_discriminant(t_cone *co, t_ray *ray)
{
	co->a = ray->dir.x * ray->dir.x
		- ray->dir.y * ray->dir.y
		+ ray->dir.z * ray->dir.z;
	co->b = 2 * ray->dir.x * ray->origin.x
		- 2 * ray->dir.y * ray->origin.y
		+ 2 * ray->dir.z * ray->origin.z;
	co->c = ray->origin.x * ray->origin.x
		- ray->origin.y * ray->origin.y
		+ ray->origin.z * ray->origin.z;
	co->disc = co->b * co->b - 4 * co->a * co->c;
}

void	cone_hit_truncate(t_shape *s, t_ray *ray, t_intersection_list **ret)
{
	t_cone	*co;
	double	t1;
	double	t2;
	double	y1;
	double	y2;

	co = (t_cone *)s->shape;
	t1 = (-1 * co->b - sqrt(co->disc)) / (2 * co->a);
	t2 = (-1 * co->b + sqrt(co->disc)) / (2 * co->a);
	y1 = ray->origin.y + dmin(t1, t2) * ray->dir.y;
	if ((co)->min < y1 && y1 < (co)->max)
		add_intersection(
			intersect_make_shape(s, dmin(t1, t2)),
			ret);
	y2 = ray->origin.y + dmax(t1, t2) * ray->dir.y;
	if ((co)->min < y2 && y2 < (co)->max)
		add_intersection(
			intersect_make_shape(s, dmax(t1, t2)),
			ret);
}

t_intersection_list	*intersection_ray_cone(t_shape *s, t_ray *ray)
{
	t_intersection_list	*ret;
	t_cone				*co;

	ret = intersection_list_make(0);
	co = (t_cone *)s->shape;
	cone_discriminant(co, ray);
	if (fabs(co->a) < 0.000001)
	{
		if (fabs(co->b) > 0.0000001)
			add_intersection(
				intersect_make_shape(
					s, -1 * co->c / 2 * co->b),
				&ret);
		co_intrs_cap(s, ray, &ret);
		return (ret);
	}
	if (co->disc < 0)
		return (ret);
	cone_hit_truncate(s, ray, &ret);
	co_intrs_cap(s, ray, &ret);
	return (ret);
}
