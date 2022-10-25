/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:41:24 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/26 00:41:26 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

int	count_shapes(int *counters)
{
	return (counters[SPH]
			+ counters[PLA]
			+ counters[SQU]
			+ counters[CUB]
			+ counters[TRI]
			+ counters[CYL]
			+ counters[CON]);
}

void	init_scene(int *counters, t_scene *scene)
{
	scene->resolution_x = -1;
	scene->resolution_y = -1;
	scene->ambi_ratio = -1;
	scene->camera_counter = 0;
	scene->cameras = (t_camera **)malloc(sizeof(t_camera *) * counters[CAM]);
	scene->light_counter = 0;
	scene->lights = (t_light **)malloc(sizeof(t_light *) * counters[LHT]);
	scene->shape_counter = 0;
	scene->shapes = (t_shape **)malloc(
			sizeof(t_shape *) * count_shapes(counters));
}

void scene_parser_postprocess(int fd, int *counters, int *success, char **line)
{
	free(counters);
	if (*success)
		*success = !(get_next_line(fd, line));
	free(*line);
	close(fd);
}

int	parse_scene(int fd, int *counters, t_scene *s)
{
	char *line;
	int cnt;
	int success;

	success = 0;
	if (get_next_line(fd, &line) && handle_r(line, s)
		&& get_next_line(fd, &line) && handle_a(line, s)) {
		success = 1;
		cnt = -1;
		while (success && ++cnt < counters[CAM])
			if (!get_next_line(fd, &line) || !handle_c(line, s, ft_itoa(cnt)))
				success = 0;
		cnt = -1;
		while (success && ++cnt < counters[LHT])
			if (!get_next_line(fd, &line) || !handle_l(line, s))
				success = 0;
		cnt = -1;
		while (success && ++cnt < count_shapes(counters))
			if (!get_next_line(fd, &line) || !handle_shape(line, s))
				success = 0;
	}
	scene_parser_postprocess(fd, counters, &success, &line);
	return (success);
}