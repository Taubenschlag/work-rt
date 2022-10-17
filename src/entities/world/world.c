/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/16 23:41:33 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	*init_world(t_world *w, t_shape **shapes, t_light **lights,
			int lights_counter)
{
	w->shapes = shapes;
	w->lights = lights;
	w->lights_counter = lights_counter;
	w->ambienace = NULL;
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
