/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/11/01 18:48:32 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_tuple	*get_tuple(char *value, char type)
{
	char	**next_part;
	int		i;
	t_tuple	*ret;

	ret = NULL;
	next_part = ft_split(value, ',');
	if (type == 'p')
		ret = tuple_point(ft_atod(next_part[0]),
				ft_atod(next_part[1]), ft_atod(next_part[2]));
	else if (type == 'v')
		ret = tuple_vector(ft_atod(next_part[0]),
				ft_atod(next_part[1]), ft_atod(next_part[2]));
	else if (type == 'c')
		ret = tuple_color(ft_atod(next_part[0]),
				ft_atod(next_part[1]), ft_atod(next_part[2]));
	i = -1;
	while (next_part[++i])
		free(next_part[i]);
	free(next_part);
	return (ret);
}

// todo move
void	cleanup(char **values)
{
	int	i;

	i = 0;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
}

void	handle_r(char **input, t_scene *s)
{
	int		i;

	i = -1;
	if (s->resolution_x < 0)
	{
		s->resolution_x = ft_atoi(input[1]);
		s->resolution_y = ft_atoi(input[2]);
	}
	else
	{
		while (input[++i])
			free(input[i]);
		free(input);
	}
	cleanup(input);
}

void	handle_a(char **input, t_scene *s)
{
	t_tuple	*color;

	s->ambi_ratio = ft_atod(input[1]);
	color = get_tuple(input[2], 'c');
	free(s->ambi_color);
	s->ambi_color = tuple_scalar_multiply(color, s->ambi_ratio * COLOR_CF);
	cleanup(input);
}

void	handle_line(char **input, t_scene *s)
{
	if (ft_strequals(input[0], "R"))
		handle_r(input, s);
	else if (ft_strequals(input[0], "A"))
		handle_a(input, s);
	else if (ft_strequals(input[0], "c"))
		handle_c(input, s);
	else if (ft_strequals(input[0], "l"))
		handle_l(input, s);
	else if (ft_strequals(input[0], "sp"))
		handle_sphere(input, s);
	else if (ft_strequals(input[0], "pl"))
		handle_plane(input, s);
	else if (ft_strequals(input[0], "sq"))
		handle_square(input, s);
	else if (ft_strequals(input[0], "cy"))
		handle_cylinder(input, s);
	else if (ft_strequals(input[0], "tr"))
		handle_triangle(input, s);
	else if (ft_strequals(input[0], "co"))
		handle_cone(input, s);
	else if (ft_strequals(input[0], "cu"))
		handle_cube(input, s);
}
