/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/21 12:22:13 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H
# include "../../../heads_global/minirt.h"

typedef struct intersection
{
	t_shape	*shape;
	double	t;
}	t_intersection;

typedef struct intersection_list
{
	int				size;
	t_intersection	**list;
}	t_intersection_list;

typedef struct computations
{
	double		t;
	t_shape		*shape;
	int			inside;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normv;
	t_tuple		overpoint;
}	t_computations;

typedef struct world
{
	int					shape_counter;
	int					lights_counter;
	t_shape				**shapes;
	t_light				**lights;
	t_light				ambienace;
	t_intersection_list	*merged;
	//t_intersection_list	**unsorted;
}	t_world;

void	make_l_p(t_lightning_pack *pack, t_light *l, t_computations *c);
void	precomp(t_computations	*comps, t_intersection *i, t_ray *r, t_tmp_m *m_tmp);
t_intersection_list		*intersect_shape(t_shape *s, t_ray *r, t_tmp_m *m_tmp);
t_intersection			*intersect_make_shape(t_shape *s, double t);
void					add_intersection(t_intersection *new_elem,
							t_intersection_list **list);
t_intersection_list		*intersection_ray_nsphere(t_shape *s, t_ray *ray);
t_intersection_list		*intersection_ray_plane(t_shape *s, t_ray *ray);
t_intersection_list		*intersection_ray_cube(t_shape *s, t_ray *ray);
t_intersection_list		*intersection_ray_cylinder(t_shape *s, t_ray *ray);
t_intersection_list		*intersection_ray_cone(t_shape *s, t_ray *ray);
t_intersection_list		*intersection_ray_triangle(t_shape *s, t_ray *ray);
t_intersection_list		*intersection_ray_square(t_shape *s, t_ray *ray);
t_intersection_list		*intersection_list_make(int elem);
t_intersection			*hit(t_intersection_list *l);
void					intersection_list_free(t_intersection_list **l);

t_intersection_list	*intersect_world(t_ray *r, t_world *w, t_tmp_m *m_tmp);

void	shade_hit(t_world *w, t_computations *cs, t_light *current, t_tmp_m *m_tmp);
void	color_at(t_world *w, t_ray *r, t_tmp_m *m_tmp);
int		in_shadow(t_world *w, t_tuple *p, t_light *current_light, t_tmp_m *m_tmp);
void	init_world(t_world *w, t_shape **shapes, t_light **lights, int lights_counter);
void	world_set_ambience(t_light *w_amb, t_tuple *from, t_tuple *color);

#endif
