/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 19:49:50 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	ray_ray(t_ray *ray, t_tuple *origin, t_tuple *direction)
{
	tuple_copy(&ray->origin, origin);
	tuple_copy(&ray->dir, direction);
}

void	ray_transform(t_ray *res, t_ray *ray, t_matrix *m)
{
	tuple_apply_trans_matrix(&res->origin, m, &ray->origin);
	tuple_apply_trans_matrix(&res->dir, m, &ray->dir);
}

void	ray_position(t_tuple *res, t_ray *ray, double t)
{
	t_tuple	tmp;

	tuple_scalar_multiply(&tmp, &ray->dir, t);
	tuple_add(res, &ray->origin, &tmp);
}
