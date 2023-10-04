/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 14:55:06 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

bool	create_files(t_scene *s)
{
	char	*filename;
	int		i;

	s->fd_list = malloc(sizeof(int) * s->counters[CAM]);
	if (s->fd_list == NULL)
	{
		printf("Error: malloc fail for *fd_list in 'init_scene()'\n");
		return (false);
	}
	i = -1;
	while (++i < s->counters[CAM])
	{
		filename = ft_strcat(ft_strdup(".bmp"), ft_itoa(i));
		s->fd_list[i] = open(filename, O_CREAT | O_WRONLY, 0);
		if (s->fd_list[i] < 0)
		{
			printf("Error: unable to create output file '%s'\n", filename);
			emergency_close(s->fd_list, i);
			free(filename);
			return (false);
		}
		free(filename);
	}
	return (true);
}

bool	save_scene(t_scene *s, int *fd_list)
{
	t_canvas	c;
	t_world		w;
	int			cam;

	w.shape_counter = s->shape_count;
	init_world(&w, s->shapes, s->lights, s->light_count);
	init_canvas(s->cameras[0]->v_size, s->cameras[0]->h_size, &c);
	cam = -1;
	while (++cam < s->camera_count)
	{
		s->cameras[cam]->cam_count = cam;
		s->cameras[cam]->cam_tot = s->camera_count;
		world_set_ambience(&w.amb, &s->cameras[cam]->from, &s->ambi_color);
		if (render(s->cameras[cam], &w, &c) == false)
			return (false);
		fill_bmp(init_bmp(s->res_y, s->res_x, fd_list[cam]), &c);
		close(fd_list[cam]);
	}
	canvas_free(&c);
	return (true);
}
