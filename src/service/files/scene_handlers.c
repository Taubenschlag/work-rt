/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 14:11:41 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

bool	handle_r(char **input, t_scene *s)
{
	if (s->res_x < 0)
	{
		s->res_x = ft_atoi(input[1]);
		s->res_y = ft_atoi(input[2]);
	}
	return (true);
}

bool	handle_a(char **input, t_scene *s)
{
	t_tuple	color;

	s->ambi_ratio = ft_atod(input[1]);
	set_tuple(&color, input[2], 'c');
	tuple_scalar_multiply(&s->ambi_color, &color, s->ambi_ratio * COLOR_CF);
	return (true);
}

bool	handle_line(char **input, t_scene *s)
{
	if (ft_strequals(input[0], "R"))
		return (handle_r(input, s));
	else if (ft_strequals(input[0], "A"))
		return (handle_a(input, s));
	else if (ft_strequals(input[0], "c"))
		return (handle_c(input, s));
	else if (ft_strequals(input[0], "l"))
		return (handle_l(input, s));
	else if (ft_strequals(input[0], "sp"))
		return (handle_sphere(input, s));
	else if (ft_strequals(input[0], "pl"))
		return (handle_plane(input, s));
	else if (ft_strequals(input[0], "sq"))
		return (handle_square(input, s));
	else if (ft_strequals(input[0], "cy"))
		return (handle_cylinder(input, s));
	else if (ft_strequals(input[0], "tr"))
		return (handle_triangle(input, s));
	else if (ft_strequals(input[0], "co"))
		return (handle_cone(input, s));
	else if (ft_strequals(input[0], "cu"))
		return (handle_cube(input, s));
	return (true);
}
