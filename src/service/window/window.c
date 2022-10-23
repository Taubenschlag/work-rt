/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/17 17:39:38 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	*argb_render(t_camera *c, t_world *w, t_canvas *img)
{
	t_ray		*r;
	t_tuple		*color;
	int			y;
	int			x;

	init_canvas(c->v_size, c->h_size, img);
	y = -1;
	while (++y < c->h_size)
	{
		x = -1;
		while (++x < c->v_size)
		{
			r = ray_for_pix(c, y, x);
			color = color_at(w, r);
			ray_free(r);
			img->canvas[y][x] = tuple_to_argb(color);
		}
	}
}

void	fill_image(t_canvas *c, t_mlx_wrap *data, int count)
{
	unsigned int	i;
	unsigned int	j;
	char			*dst;

	i = c->h;
	while (--i > 0)
	{
		j = c->w;
		while (--j > 0)
		{
			dst = data->addr[count]
				+ (i * data->line_length + j * (data->bits_per_pixel / 8));
			*(unsigned int *)dst = c->canvas[i][j];
		}
	}
}

void	loop_gui(t_mlx_wrap *data)
{
	data->img_ptr = 1;
	mlx_put_image_to_window(
		data->mlx, data->win, data->imgs[data->img_ptr], 0, 0);
	mlx_hook(data->win, 17, 131072, w_close, data);
	mlx_hook(data->win, 2, 1, k_press, data);
	mlx_loop(data->mlx);
}

t_mlx_wrap	*init_mlx_wrapper(t_scene *s)
{
	t_mlx_wrap	*data;

	data = malloc(sizeof(t_mlx_wrap));
	data->mlx = mlx_init();
	data->imgs = malloc(sizeof(void *) * (s->camera_counter + 2));
	data->addr = malloc(sizeof(char *) * (s->camera_counter + 2));
	data->imgs[s->camera_counter + 1] = NULL;
	data->imgs[0] = NULL;
	data->win = mlx_new_window(
			data->mlx, s->resolution_x, s->resolution_y, "miniRT");
	data->img_counter = s->camera_counter;
	return (data);
}

void	display_scene(t_scene *s)
{
	t_mlx_wrap	*data;
	t_canvas	c;
	t_world		w;
	int			cam_count;

	cam_count = 0;
	w.shape_counter = s->shape_counter;
	init_world(&w, s->shapes, s->lights, s->light_counter);
	data = init_mlx_wrapper(s);
	while (++cam_count <= s->camera_counter)
	{
		world_set_ambience(&w, s->cameras[cam_count - 1]->from, s->ambi_color);
		argb_render(s->cameras[cam_count - 1], &w, &c);
		free(s->cameras[cam_count - 1]->name);
		data->imgs[cam_count] = mlx_new_image(
				data->mlx, s->resolution_x, s->resolution_y);
		data->addr[cam_count] = mlx_get_data_addr(
				data->imgs[cam_count], &(data->bits_per_pixel),
				&(data->line_length), &(data->endian));
		fill_image(&c, data, cam_count);
		canvas_free(&c);
	}
	if (w.ambienace)
		light_free(w.ambienace);
	loop_gui(data);
}
