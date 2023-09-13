/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:41:24 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/13 18:01:40 by sbocanci         ###   ########.fr       */
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
	scene->ambi_color = tuple_color(0, 0, 0);
	scene->camera_counter = 0;
	scene->cameras = (t_camera **)malloc(sizeof(t_camera *) * counters[CAM]);
	scene->light_counter = 0;
	scene->lights = (t_light **)malloc(sizeof(t_light *) * counters[LHT]);
	scene->shape_counter = 0;
	scene->shapes = (t_shape **)malloc(
			sizeof(t_shape *) * count_what(counters, SHAPES));
}

void	parse_scene(int fd, int *counters, t_scene *s)
{
	char	*line;
	/* DEBUG */
	//int	i = -1;
	/* ******/

	while (get_next_line(fd, &line))
	{
		//if (++i < 3 && line && !ft_strequals(line, ""))
		if (line && !ft_strequals(line, ""))
		{
			/* DEBUG */
			printf("parce_scene, line:[%s]\n", line);
			/* ***** */
			handle_line(ft_whitespaces(line), s);
			/* DEBUG */
			//printf("parce_scene, line:[%s]\nexit\n", line);
			/* ***** */
		}
		free(line);
	}
	/* DEBUG */
	printf("\tlast line:[%s]\n", line);
	//exit(0);
	/* ***** */
	if (line && !ft_strequals(line, ""))
		handle_line(ft_whitespaces(line), s);
	free(line);
	free(counters);
	close(fd);
}
