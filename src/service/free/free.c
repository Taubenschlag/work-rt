/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:33:58 by sbocanci          #+#    #+#             */
/*   Updated: 2023/09/29 18:58:00 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	free_scene(t_scene *s)
{
	int	i;

	i = -1;
	while (++i < s->camera_count)
		free_camera(s->cameras[i]);
	free(s->cameras);
	i = -1;
	while (++i < s->shape_count)
		free_shape(s->shapes[i]);
	free(s->shapes);
	i = -1;
	while (++i < s->light_count)
		light_free(s->lights[i]);
	free(s->lights);
	if (s->fd_list)
		free(s->fd_list);
}

void	cleanup(char **values)
{
	int	i;

	i = 0;
	if (values)
	{
		if (values[i])
			while (values[i])
				free(values[i++]);
		free(values);
	}
}

void	emergency_close(int *fds, int failed)
{
	failed--;
	while (failed >= 0)
	{
		close(fds[failed]);
		failed--;
	}
}

void	canvas_free(t_canvas *c)
{
	unsigned int	i;

	i = 0;
	while (i < c->h)
	{
		free(c->canvas[i]);
		i++;
	}
	free(c->canvas);
}

void	free_camera(t_camera *c)
{
	if (c)
	{
		free(c);
	}
}
