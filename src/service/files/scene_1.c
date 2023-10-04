/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:41:24 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 14:10:54 by sbocanci         ###   ########.fr       */
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

static void	init_scene_helper(t_scene *scene)
{
	scene->res_x = -1;
	scene->res_y = -1;
	scene->ambi_ratio = -1;
	tuple_color(&scene->ambi_color, 0, 0, 0);
	scene->camera_count = 0;
	scene->light_count = 0;
	scene->shape_count = 0;
	scene->fd_list = NULL;
}

bool	init_scene(t_scene *s)
{
	init_scene_helper(s);
	s->cameras = (t_camera **)malloc(sizeof(t_camera *) * s->counters[CAM]);
	if (s->cameras == NULL)
	{
		printf("Error: malloc fail for **cameras in 'init_scene()'\n");
		return (false);
	}
	s->lights = (t_light **)malloc(sizeof(t_light *) * s->counters[LHT]);
	if (s->lights == NULL)
	{
		printf("Error: malloc fail for **lights in 'init_scene()'\n");
		return (false);
	}
	s->shapes = (t_shape **)malloc(
			sizeof(t_shape *) * count_what(s->counters, SHAPES));
	if (s->shapes == NULL)
	{
		printf("Error: malloc fail for **shapes in 'init_scene()'\n");
		return (false);
	}
	return (true);
}

bool	parse_scene(t_scene *s)
{
	char	line[GNL_BUF_SIZE];
	char	*l;
	char	**split;

	l = get_next_line(s->fd_infile, line);
	while (l != NULL)
	{
		if (l && !ft_strequals(line, "") && find_first('#', line) != 0)
		{
			if (find_first('#', line) > 0)
				line[find_first('#', line)] = '\0';
			split = ft_whitespaces(line);
			if (!handle_line(split, s))
			{
				cleanup(split);
				return (false);
			}
			cleanup(split);
		}
		l = get_next_line(s->fd_infile, line);
	}
	close(s->fd_infile);
	return (true);
}
