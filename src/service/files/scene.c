/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/09/30 22:43:48 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

s_scene	*make_scene(int *counters)
{
	s_scene	*ret;

	ret = (s_scene *)malloc(sizeof(s_scene));
	ret->resolution_x = -1;
	ret->resolution_y = -1;
	ret->ambi_ratio = -1;
	ret->camera_counter = 0;
	ret->cameras = (s_camera **)malloc(sizeof(s_camera *) * counters[2]);
	ret->light_counter = 0;
	ret->lights = (s_light **)malloc(sizeof(s_light *) * counters[3]);
	ret->shape_counter = 0;
	ret->shapes = (s_shape **)malloc(sizeof(s_shape *) * counters[4]);
	return (ret);
}

int	throw_err(int error)
{
	if (error)
	{
		perror("invalid file");
		return (1);
	}
	return (0);
}

// TODO more than 25 lines
s_scene	*parse_scene(int fd, int *counters)
{
	char	*line;
	int		cnt;
	int		error;
	s_scene	*sc;

	sc = make_scene(counters);
	error = 0;
	if (get_next_line(fd, &line) && handle_r(line, sc)
		&& get_next_line(fd, &line) && handle_a(line, sc))
	{
		cnt = -1;
		while (!error && ++cnt < counters[2])
			if (!get_next_line(fd, &line) || !handle_c(line, sc, ft_itoa(cnt)))
				error = 1;
		cnt = -1;
		while (!error && ++cnt < counters[3])
			if (!get_next_line(fd, &line) || !handle_l(line, sc))
				error = 1;
		cnt = -1;
		while (!error && ++cnt < counters[4])
			if (!get_next_line(fd, &line) || !handle_shape(line, sc))
				error = 1;
		if (throw_err(error))
			return (NULL);
	}
	return (sc);
}

void	free_scene(s_scene *s)
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
	free(s);
}

void	save_scene(s_scene *s)
{
	s_canvas	*c;
	s_world		*w;
	char		*filename;
	int			fd;
	int			camera_counter;

	camera_counter = -1;
	w = make_world(s->shapes, s->lights, s->shape_counter, s->light_counter);
	while (++camera_counter < s->camera_counter)
	{
		world_set_ambience(w, s->cameras[camera_counter]->from, s->ambi_color);
		filename = ft_strcat(
				ft_strdup(".bmp"), s->cameras[camera_counter]->name);
		fd = open(filename, O_CREAT | O_WRONLY, 0);
		free(filename);
		c = render(s->cameras[camera_counter], w);
		fill_bmp(init_bmp(s->resolution_y, s->resolution_x, fd), c);
		close(fd);
		canvas_free(c);
	}
	if (w->ambienace)
		light_free(w->ambienace);
	free_scene(s);
	free(w);
}
