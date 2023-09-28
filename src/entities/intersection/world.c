/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/21 18:49:30 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	init_world(t_world *w, t_shape **shapes, t_light **lights,
			int lights_counter)
{
	w->shapes = shapes;
	w->lights = lights;
	w->lights_counter = lights_counter;
	w->merged = NULL;
}

void	world_set_ambience(t_light *w_amb, t_tuple *from, t_tuple *color)
{
	tuple_copy(&w_amb->position, from);
	tuple_copy(&w_amb->color, color);
}
