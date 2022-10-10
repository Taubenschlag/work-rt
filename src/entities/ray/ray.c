/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 22:28:44 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_ray	*ray_ray(t_tuple *origin, t_tuple *direction)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	ray->origin = origin;
	ray->dir = direction;
	return (ray);
}

void	ray_free(t_ray *ray)
{
	tuple_free((ray->origin));
	tuple_free((ray->dir));
	free(ray);
}

t_ray	*ray_transform(t_ray *ray, t_matrix *m)
{
	t_matrix	*m1;

	m1 = matrix_copy(m);
	return (ray_ray(
			tuple_apply_trans_matrix(m1, tuple_copy(ray->origin)),
			tuple_apply_trans_matrix(m, tuple_copy(ray->dir))));
}

t_tuple	*ray_position(t_ray *ray, double t)
{
	return (tuple_add(
			tuple_copy(ray->origin),
			tuple_scalar_multiply(tuple_copy(ray->dir), t)));
}
