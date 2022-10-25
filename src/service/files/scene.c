/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/23 18:18:43 by rokupin          ###   ########.fr       */
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

int	parse_scene(int fd, int *counters, t_scene *s)
{
	char	*line;
	int		cnt;
	int		success;

	success = 0;
	if (get_next_line(fd, &line) && handle_r(line, s)
		&& get_next_line(fd, &line) && handle_a(line, s))
	{
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
			if (!get_next_line(fd, &line) ||
			!handle_shape(line, s))
				success = 0;
	}
	free(counters);
	success = !(get_next_line(fd, &line));
	free(line);
	close(fd);
	return (success);
}

void	free_scene(t_scene *s)
{
	int	i;

	i = -1;
	while (++i < s->camera_counter)
		free_camera(s->cameras[i]);
	free(s->cameras);
	i = -1;
	while (++i < s->shape_counter)
		free_shape(s->shapes[i]);
	free(s->shapes);
	i = -1;
	while (++i < s->light_counter)
		light_free(s->lights[i]);
	free(s->lights);
	free(s->ambi_color);
}

void	save_scene(t_scene *s)
{
	t_canvas	c;
	t_world		w;
	char		*filename;
	int			fd;
	int			cam_count;

	cam_count = -1;
	w.shape_counter = s->shape_counter;
	init_world(&w, s->shapes, s->lights, s->light_counter);
	while (++cam_count < s->camera_counter)
	{
		world_set_ambience(&w, s->cameras[cam_count]->from, s->ambi_color);
		filename = ft_strcat(
				ft_strdup(".bmp"), s->cameras[cam_count]->name);
		fd = open(filename, O_CREAT | O_WRONLY, 0);
		free(filename);
		render(s->cameras[cam_count], &w, &c);
		fill_bmp(init_bmp(s->resolution_y, s->resolution_x, fd), &c);
		close(fd);
		canvas_free(&c);
	}
	if (w.ambienace)
		light_free(w.ambienace);
	free_scene(s);
}
