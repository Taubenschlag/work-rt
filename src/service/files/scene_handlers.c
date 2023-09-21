/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/21 18:51:05 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	set_tuple(t_tuple *tuple, char *value, char type)
{
	char	**input;

	input = ft_split(value, ',');
	tuple->x = ft_atod(input[0]);
	tuple->y = ft_atod(input[1]);
	tuple->z = ft_atod(input[2]);
	if (type == 'p')
		tuple->type = IS_POINT;
	if (type == 'v')
		tuple->type = IS_VECTOR;
	if (type == 'c')
		tuple->type = 2;
	cleanup(input);
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
	t_tuple	color;

	s->ambi_ratio = ft_atod(input[1]);
	set_tuple(&color, input[2], 'c');
	tuple_scalar_multiply(&s->ambi_color, &color, s->ambi_ratio * COLOR_CF);
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
