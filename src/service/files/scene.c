/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/11/04 22:56:17 by rokupin          ###   ########.fr       */
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

void	emergency_close(int *fds, int failed)
{
	failed--;
	while (failed >= 0)
	{
		close(fds[failed]);
		failed--;
	}
	free(fds);
}

int	*create_files(int *counters)
{
	int		*fd_list;
	char	*filename;
	int		i;

	i = 0;
	fd_list = malloc(sizeof(int) * counters[CAM]);
	while (i < counters[CAM])
	{
		filename = ft_strcat(
				ft_strdup(".bmp"), ft_itoa(i));
		fd_list[i] = open(filename, O_CREAT | O_WRONLY, 0);
		free(filename);
		if (fd_list[i] < 0)
		{
			free(counters);
			emergency_close(fd_list, i);
			return (NULL);
		}
		i++;
	}
	return (fd_list);
}

void	save_scene(t_scene *s, int *fd_list)
{
	t_canvas	c;
	t_world		w;
	int			cam_count;

	cam_count = -1;
	w.shape_counter = s->shape_counter;
	init_world(&w, s->shapes, s->lights, s->light_counter);
	while (++cam_count < s->camera_counter)
	{
		world_set_ambience(&w, s->cameras[cam_count]->from, s->ambi_color);
		render(s->cameras[cam_count], &w, &c);
		fill_bmp(init_bmp(
				s->resolution_y, s->resolution_x, fd_list[cam_count]), &c);
		close(fd_list[cam_count]);
		canvas_free(&c);
	}
	if (w.ambienace)
		light_free(w.ambienace);
	free_scene(s);
	free(fd_list);
}
