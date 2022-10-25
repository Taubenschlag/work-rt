/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/26 00:32:11 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

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
