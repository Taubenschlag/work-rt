/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 22:27:25 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "../../../heads_global/minirt.h"

typedef struct ray
{
	t_tuple	*origin;
	t_tuple	*dir;
}	t_ray;

t_ray	*ray_ray(t_tuple *origin, t_tuple *direction);
t_tuple	*ray_position(t_ray *ray, double t);
t_ray	*ray_transform(t_ray *ray, t_matrix *m);
void	ray_free(t_ray *p_ray);

#endif //RT_CHALLENGE_RAY_H
