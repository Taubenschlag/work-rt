/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:41:24 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/22 13:47:30 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

int	count_what(int *counters, int what)
{
	int	i;
	int	res;

	if (what == SHAPES)
		return (counters[SPH]
			+ counters[PLA]
			+ counters[SQU]
			+ counters[CUB]
			+ counters[TRI]
			+ counters[CYL]
			+ counters[CON]);
	else if (what == ALL)
	{
		i = -1;
		res = 0;
		while (++i < INSTRUCTION_SET_SIZE)
			res += counters[i];
		return (res);
	}
	return (-1);
}

void	init_scene(int *counters, t_scene *scene)
{
	scene->resolution_x = -1;
	scene->resolution_y = -1;
	scene->ambi_ratio = -1;
	tuple_color(&scene->ambi_color, 0, 0, 0);
	scene->camera_count = 0;
	scene->cameras = (t_camera **)malloc(sizeof(t_camera *) * counters[CAM]);
	scene->light_count = 0;
	scene->lights = (t_light **)malloc(sizeof(t_light *) * counters[LHT]);
	scene->shape_count = 0;
	scene->shapes = (t_shape **)malloc(
			sizeof(t_shape *) * count_what(counters, SHAPES));
}

bool	parse_scene(int fd, t_scene *s)
{
	char	line[GNL_BUF_SIZE];
	char	*l;
	char	**split;

	l = get_next_line(fd, line);
	while (l != NULL)
	{
		if (l && !ft_strequals(line, ""))
		{
			split = ft_whitespaces(line);
			if (!handle_line(split, s))
			{
				cleanup(split);
				return (false);
			}
			cleanup(split);
		}
		l = get_next_line(fd, line);
	}
	close(fd);
	return (true);
}

/*
void	parse_scene(int fd, t_scene *s)
{
	char	line[GNL_BUF_SIZE];
	char	*l;
	char	**split;

	l = get_next_line(fd, line);
	while (l != NULL)
	{
		if (l && !ft_strequals(line, ""))
		{
			handle_line(ft_whitespaces(line), s);
		}
		l = get_next_line(fd, line);
	}
	close(fd);
}
*/