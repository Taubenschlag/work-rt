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

// todo too much args
double	init(t_shape *s, t_ray *ray, t_intersection_list **ret,
			   t_tuple **dir_cros, double *dot)
{
	*ret = intersection_list_make(0);
	*dir_cros = tuple_cross_product(ray->dir, ((t_triangle *)s->shape)->e2);
	*dot = tuple_dot_product(((t_triangle *)s->shape)->e1, *dir_cros);
	return (1.0 / *dot);
}

//? TODO more than 25
t_intersection_list	*intersection_ray_triangle(t_shape *s, t_ray *ray)
{
	t_tuple				*dir_cros;
	t_tuple				*or_crs;
	t_tuple				*a_to_origin;
	double				dots[5];
	t_intersection_list	*ret;

	dots[0] = init(s, ray, &ret, &dir_cros, &(dots[4]));
	if (fabs(dots[4]) < 0.0001 && cheaty_free(dir_cros))
		return (ret);
	a_to_origin = tuple_substract(tuple_copy(ray->origin),
			tuple_copy(((t_triangle *)s->shape)->a));
	dots[1] = dots[0] * tuple_dot_product(a_to_origin, dir_cros);
	free(dir_cros);
	if ((dots[1] < 0 - 0.0001
			|| dots[1] > 1 + 0.00001) && cheaty_free(a_to_origin))
		return (ret);
	or_crs = tuple_cross_product(a_to_origin, ((t_triangle *)s->shape)->e1);
	dots[2] = dots[0] * tuple_dot_product(ray->dir, or_crs);
	free(a_to_origin);
	if ((dots[2] < 0 - 0.0001
			|| (dots[2] + dots[1]) > 1 + 0.00001) && cheaty_free(or_crs))
		return (ret);
	dots[3] = dots[0] * tuple_dot_product(((t_triangle*)s->shape)->e2, or_crs);
	add_intersection(intersect_make_shape(s, dots[3]), &ret);
	free(or_crs);
	return (ret);
}

//todo too long
t_intersection_list	*intersection_ray_square(t_shape *s, t_ray *ray)
{
	t_intersection_list	*ret;
	t_intersection_list	*temp;
	t_shape				*tr;
	t_square			*q;

	q = (t_square *)s->shape;
	tr = make_shape('i', (t_triangle *)q->t1);
	temp = intersection_ray_triangle(tr, ray);
	matrix_free(tr->trans);
	free(tr);
	tr = make_shape('i', (t_triangle *)q->t2);
	ret = intersection_ray_triangle(tr, ray);
	matrix_free(tr->trans);
	free(tr);
	if (temp->size == 1 && ret->size == 1)
		intersection_list_free(temp);
	if (temp->size == 1 && ret->size == 0)
	{
		add_intersection(temp->list[0], &ret);
		free(temp->list);
	}
	if (ret->size == 1)
		ret->list[0]->shape = s;
	// if(temp->list)
	//     free(temp->list);
	free(temp);
	return (ret);
}
