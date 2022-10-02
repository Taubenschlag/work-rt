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

typedef struct t_ray
{
	s_tuple	*origin;
	s_tuple	*dir;
}	s_ray;

s_ray	*ray_ray(s_tuple *origin, s_tuple *direction);
s_tuple	*ray_position(s_ray *ray, double t);
s_ray	*ray_transform(s_ray *ray, s_matrix *m);
void	ray_free(s_ray *p_ray);

#endif //RT_CHALLENGE_RAY_H
