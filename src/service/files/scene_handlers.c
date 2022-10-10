/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/09/30 23:03:28 by rokupin          ###   ########.fr       */
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

int	handle_r(char *line, t_scene *s)
{
	int		i;
	char	**input;

	input = ft_whitespaces(line);
	free(line);
	i = -1;
	if (input && ft_strequals(input[0], "R"))
	{
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
			return (0);
		}
	}
	cleanup(input);
	return (s->resolution_x > 0 && s->resolution_y > 0);
}

int	handle_a(char *line, t_scene *s)
{
	char	**input;
	t_tuple	*color;

	input = ft_whitespaces(line);
	free(line);
	if (input && ft_strequals(input[0], "A"))
	{
		if (s->ambi_ratio < 0)
			s->ambi_ratio = ft_atod(input[1]);
		else
			s->ambi_ratio = -1;
		color = get_tuple(input[2], 'c');
		s->ambi_color = tuple_scalar_multiply(color, s->ambi_ratio * COLOR_CF);
	}
	cleanup(input);
	return (s->ambi_ratio >= 0 && s->ambi_ratio <= 1);
}

int	handle_shape(char *line, t_scene *s)
{
	char	**input;

	input = ft_whitespaces(line);
	free(line);
	if (input && ft_strequals(input[0], "sp"))
		return (handle_sphere(input, s));
	if (input && ft_strequals(input[0], "pl"))
		return (handle_plane(input, s));
	if (input && ft_strequals(input[0], "sq"))
		return (handle_square(input, s));
	if (input && ft_strequals(input[0], "cy"))
		return (handle_cylinder(input, s));
	if (input && ft_strequals(input[0], "tr"))
		return (handle_triangle(input, s));
	if (input && ft_strequals(input[0], "co"))
		return (handle_cone(input, s));
	if (input && ft_strequals(input[0], "cu"))
		return (handle_cube(input, s));
	return (0);
}
