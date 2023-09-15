/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/15 17:59:56 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

int	in_shadow(t_world *w, t_tuple *p, t_light *current_light, t_tmp_m *m_tmp)
{
	t_tuple			*v;
	double			dist;
	t_tuple			*direction;
	t_ray			*ray;
	t_intersection	*h;

	v = tuple_substract(tuple_copy(current_light->position), tuple_copy(p));
	dist = tuple_length(v);
	direction = tuple_normalize(v);
	ray = ray_ray(p, direction);
	h = hit(intersect_world(ray, w, m_tmp));
	ray_free(ray);
	if (h && (dist - h->t) > 0.00001)
	{
		free(h);
		return (1);
	}
	if (h)
		free(h);
	return (0);
}

t_intersection_list	*intersection_ray_plane(t_shape *s, t_ray *ray)
{
	t_intersection_list	*ret;

	if (fabs(ray->dir->y) < 0.000001)
		return (intersection_list_make(0));
	else
	{
		ret = intersection_list_make(1);
		ret->list[0] = intersect_make_shape(
				s, (-1 * ray->origin->y) / ray->dir->y);
		return (ret);
	}
}

t_intersection_list	*intersection_ray_nsphere(t_shape *s, t_ray *ray)
{
	t_tuple				*sphere_ray;
	double				a;
	double				b;
	double				dis;
	t_intersection_list	*ret;

	sphere_ray = tuple_substract(tuple_copy(ray->origin),
			tuple_copy(((t_sphere*)s->shape)->centre));
	a = tuple_dot_product(ray->dir, ray->dir);
	b = 2 * tuple_dot_product(ray->dir, sphere_ray);
	dis = b * b - 4 * a * (tuple_dot_product(sphere_ray, sphere_ray) - 1);
	tuple_free(sphere_ray);
	if (dis < 0)
		return (intersection_list_make(0));
	ret = intersection_list_make(2);
	ret->list[0] = intersect_make_shape(s, (-1 * b - sqrt(dis)) / (2 * a));
	ret->list[1] = intersect_make_shape(s, (-1 * b + sqrt(dis)) / (2 * a));
	return (ret);
}

void	axis(double orig, double direct, double *min, double *max)
{
	double	t_min_temp;
	double	t_max_temp;
	double	t_min;
	double	t_max;

	t_min_temp = -1 - orig;
	t_max_temp = 1 - orig;
	if (fabs(direct) >= 0.00001)
	{
		t_min = t_min_temp / direct;
		t_max = t_max_temp / direct;
	}
	else
	{
		t_min = t_min_temp * INFINITY;
		t_max = t_max_temp * INFINITY;
	}
	if (t_max >= t_min)
		*max = t_max;
	else
		*max = t_min;
	if (t_min <= t_max)
		*min = t_min;
	else
		*min = t_max;
}

t_intersection_list	*intersection_ray_cube(t_shape *s, t_ray *ray)
{
	t_intersection_list	*ret;
	double				*mints;
	double				*maxts;
	double				min;
	double				max;

	mints = (double *)malloc(sizeof(double) * 3);
	maxts = (double *)malloc(sizeof(double) * 3);
	axis(ray->origin->x, ray->dir->x, &(mints[0]), &(maxts[0]));
	axis(ray->origin->y, ray->dir->y, &(mints[1]), &(maxts[1]));
	axis(ray->origin->z, ray->dir->z, &(mints[2]), &(maxts[2]));
	min = maxs(mints, 3);
	max = mins(maxts, 3);
	if (min > max)
	{
		free(mints);
		free(maxts);
		return (intersection_list_make(0));
	}
	ret = intersection_list_make(2);
	ret->list[0] = intersect_make_shape(s, min);
	ret->list[1] = intersect_make_shape(s, max);
	free(mints);
	free(maxts);
	return (ret);
}
