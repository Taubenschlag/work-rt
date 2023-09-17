/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 19:50:19 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "../../../heads_global/minirt.h"

typedef struct ray
{
	t_tuple	origin;
	t_tuple	dir;
}	t_ray;

void	ray_ray(t_ray *ray, t_tuple *origin, t_tuple *direction);
void	ray_transform(t_ray *res, t_ray *ray, t_matrix *m);
void	ray_position(t_tuple *res, t_ray *ray, double t);

#endif
