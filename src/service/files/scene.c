/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/14 21:54:20 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_scene	*make_scene(int *counters)
{
	t_scene	*ret;

	ret = (t_scene *)malloc(sizeof(t_scene));
	ret->resolution_x = -1;
	ret->resolution_y = -1;
	ret->ambi_ratio = -1;
	ret->camera_counter = 0;
	ret->cameras = (t_camera **)malloc(sizeof(t_camera *) * counters[CAM]);
	ret->light_counter = 0;
	ret->lights = (t_light **)malloc(sizeof(t_light *) * counters[LHT]);
	ret->shape_counter = 0;
	ret->shapes = (t_shape **)malloc(sizeof(t_shape *)
			* (counters[SPH]
				+ counters[PLA]
				+ counters[SQU]
				+ counters[CUB]
				+ counters[TRI]
				+ counters[CYL]
				+ counters[CON]));
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

void	parse_scene(int fd, int *countrs, t_scene **s)
{
	char	*line;
	int		cnt;
	int		error;

	*s = make_scene(countrs);
	error = 0;
	if (get_next_line(fd, &line) && handle_r(line, *s)
		&& get_next_line(fd, &line) && handle_a(line, *s))
	{
		cnt = -1;
		while (!error && ++cnt < countrs[CAM])
			if (!get_next_line(fd, &line) || !handle_c(line, *s, ft_itoa(cnt)))
				error = 1;
		cnt = -1;
		while (!error && ++cnt < countrs[LHT])
			if (!get_next_line(fd, &line) || !handle_l(line, *s))
				error = 1;
		cnt = -1;
		while (!error && ++cnt < (countrs[SPH] + countrs[PLA] + countrs[SQU]
				+ countrs[CUB] + countrs[TRI] + countrs[CYL] + countrs[CON]))
			if (!get_next_line(fd, &line) || !handle_shape(line, *s))
				error = 1;
		if (throw_err(error))
			*s = NULL;
	}
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
	free(s);
}

void	save_scene(t_scene *s)
{
	t_canvas	*c;
	t_world		*w;
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
