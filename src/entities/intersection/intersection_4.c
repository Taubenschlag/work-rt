/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 16:26:35 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

// todo ternary
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
	*max = t_max > t_min ? t_max : t_min;
	*min = t_max < t_min ? t_max : t_min;
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

//? TODO more than 25
t_intersection_list	*intersection_ray_triangle(t_shape *s, t_ray *ray)
{
	t_tuple				*dir_cros;
	t_tuple				*or_crs;
	t_tuple				*a_to_origin;
	double				det;
	double				f;
	double				u;
	double				v;
	double				t;
	t_intersection_list	*ret;

	ret = intersection_list_make(0);
	dir_cros = tuple_cross_product(ray->dir, ((t_triangle *)s->shape)->e2);
	det = tuple_dot_product(((t_triangle *)s->shape)->e1, dir_cros);
	if (fabs(det) < 0.0001)
	{
		free(dir_cros);
		return (ret);
	}
	f = 1.0 / det;
	a_to_origin = tuple_substract(tuple_copy(ray->origin), tuple_copy(((t_triangle *)s->shape)->a));
	u = f * tuple_dot_product(a_to_origin, dir_cros);
	free(dir_cros);
	if (u < 0 - 0.0001 || u > 1 + 0.00001)
	{
		free(a_to_origin);
		return (ret);
	}
	or_crs = tuple_cross_product(a_to_origin, ((t_triangle *)s->shape)->e1);
	v = f * tuple_dot_product(ray->dir, or_crs);
	free(a_to_origin);
	if (v < 0 - 0.0001 || (v + u) > 1 + 0.00001)
	{
		free(or_crs);
		return (ret);
	}
	t = f * tuple_dot_product(((t_triangle*)s->shape)->e2, or_crs);
	add_intersection(intersect_make_shape(s, t), &ret);
	free(or_crs);
	return (ret);
}

t_intersection_list	*intersection_ray_square(t_shape *s, t_ray *ray)
{
	t_intersection_list	*ret;
	t_intersection_list	*temp;
	t_shape				*tr;
	t_square			*q;

	q = (t_square *)s->shape;
	tr = make_shape('i', (t_triangle *)q->t2);
	ret = intersection_ray_triangle(tr, ray);
	matrix_free(tr->trans);
	free(tr);
	if (ret->size == 1)
	{
		ret->list[0]->shape = s;
		return (ret);
	}
	intersection_list_free(&ret);
	tr = make_shape('i', (t_triangle *)q->t1);
	temp = intersection_ray_triangle(tr, ray);
	matrix_free(tr->trans);
	free(tr);
	if (temp->size == 1)
		temp->list[0]->shape = s;
	return (temp);
}
