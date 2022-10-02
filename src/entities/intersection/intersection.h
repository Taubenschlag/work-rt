/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 03:28:28 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H
# include "../../../heads_global/minirt.h"

typedef struct t_intersection
{
	s_shape	*shape;
	double	t;
}	s_intersection;

typedef struct t_intersection_list
{
	int				size;
	s_intersection	**list;
}	s_intersection_list;

typedef struct t_computations
{
	double		t;
	s_shape		*shape;
	int			inside;
	s_tuple		*point;
	s_tuple		*eyev;
	s_tuple		*normv;
	s_tuple		*overpoint;
}	s_computations;

s_computations			*precomp(s_intersection *i, s_ray *r);
s_intersection_list		*intersect_shape(s_shape *s, s_ray *r);
s_intersection			*intersect_make_shape(s_shape *s, double t);
void					add_intersection(s_intersection *new_elem,
							s_intersection_list **list);
s_intersection_list		*intersection_ray_nsphere(s_shape *s, s_ray *ray);
s_intersection_list		*intersection_ray_plane(s_shape *s, s_ray *ray);
s_intersection_list		*intersection_ray_cube(s_shape *s, s_ray *ray);
s_intersection_list		*intersection_ray_cylinder(s_shape *s, s_ray *ray);
s_intersection_list		*intersection_ray_cone(s_shape *s, s_ray *ray);
s_intersection_list		*intersection_ray_triangle(s_shape *s, s_ray *ray);
s_intersection_list		*intersection_ray_square(s_shape *s, s_ray *ray);
s_intersection_list		*intersection_list_make(int elem);
s_intersection			*hit(s_intersection_list *l);
s_tuple					*shade_hit(s_world *w, s_computations *cs,
							s_light *current);
s_intersection_list		*intersect_world(s_ray *r, s_world *w);
s_tuple					*color_at(s_world *w, s_ray *r);
int						in_shadow(s_world *w, s_tuple *p,
							s_light *current_light);
void					intersection_list_free(s_intersection_list *l);

#endif
