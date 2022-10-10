/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 01:43:31 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_world	*make_world(t_shape **shapes,
					   t_light **lights, int shape_counter, int light_counter)
{
	t_world	*w;

	w = (t_world *)malloc(sizeof(t_world));
	w->shapes = shapes;
	w->lights = lights;
	w->lights_counter = light_counter;
	w->shape_counter = shape_counter;
	w->ambienace = NULL;
	return (w);
}

t_world	*make_default_world(void)
{
	t_shape		**shapes;
	t_sphere	*s1;
	t_sphere	*s2;
	t_light		**lights;

	shapes = (t_shape **)malloc(sizeof(t_shape *) * 2);
	s1 = nsphere_unit(tuple_point(0, 0, 0));
	s2 = nsphere_unit(tuple_point(0, 0, 0));
	shapes[0] = make_shape('s', s1);
	shapes[1] = make_shape('s', s2);
	shapes[0]->matrl = material_make_default();
	shapes[1]->matrl = material_make_default();
	shapes[0]->matrl->specular = 0.2;
	shapes[0]->matrl->diffuse = 0.7;
	shapes[0]->matrl->color = tuple_color(0.8, 1.0, 0.6);
	set_transform(shapes[1], matrix_scale(0.5, 0.5, 0.5));
	lights = (t_light **)malloc(sizeof(t_light *));
	*lights = light_make(tuple_point(-10, 10, -10),
			tuple_color(1, 1, 1));
	return (make_world(shapes, lights, 2, 1));
}

void	free_world_deep(t_world *w)
{
	while (--(w->shape_counter) >= 0)
		free_shape(w->shapes[w->shape_counter]);
	while (--(w->lights_counter) >= 0)
		light_free(w->lights[w->lights_counter]);
	if (w->ambienace)
		light_free(w->ambienace);
	free(w->shapes);
	free(w->lights);
	free(w);
}

void	world_set_ambience(t_world *w, t_tuple *from, t_tuple *color)
{
	if (w->ambienace)
		light_free(w->ambienace);
	w->ambienace = light_make(tuple_point(from->x, from->y, from->z),
			tuple_color(color->x, color->y, color->z));
}
