/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 01:40:35 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H
# include "../../../heads_global/minirt.h"

//TODO struct must start with t
typedef struct t_world
{
	int		shape_counter;
	int		lights_counter;
	s_shape	**shapes;
	s_light	**lights;
	s_light	*ambienace;
}	s_world;

s_world	*make_world(s_shape **shapes, s_light **lights, int shape_counter,
			int light_counter);
void	world_set_ambience(s_world *w, s_tuple *from, s_tuple *color);
s_world	*make_default_world(void);
void	free_world_deep(s_world *w);

#endif