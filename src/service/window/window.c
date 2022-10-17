/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/09/30 22:35:22 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	went_out(t_mlx_wrap *data)
{
	int	i;

	i = 1;
	free(data->imgs[0]);
	free(data->imgs[data->img_counter + 1]);
	while (i <= data->img_counter)
	{
		mlx_destroy_image(data->mlx, data->imgs[i]);
		// TODO wtf?
		// free(data->imgs[i]);
		// free(data->addr[i]);
		i++;
	}
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	free(data);
	exit(EXIT_SUCCESS);
}

void *argb_render(t_camera *c, t_world *w, t_canvas *img)
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

//TODO too much args
void	my_mlx_pixel_put(t_mlx_wrap *data,
						 unsigned int x, unsigned int y, int color, int count)
{
	char	*dst;

	dst = data->addr[count]
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	fill_image(t_canvas *c, t_mlx_wrap *data, int count)
{
	unsigned int	i;
	unsigned int	j;

	i = c->h;
	while (--i > 0)
	{
		j = c->w;
		while (--j > 0)
		{
			my_mlx_pixel_put(data, j, i, c->canvas[i][j], count);
		}
	}
}

int	w_close(t_mlx_wrap *data)
{
	went_out(data);
	return (1);
}

//TODO too much func
int	k_press(int keycode, t_mlx_wrap *data)
{
	int	next;
	int	prev;

	next = data->img_ptr + 1;
	prev = data->img_ptr - 1;
	if (keycode == 65307)
		went_out(data);
	if (keycode == 65363 && data->imgs[next])
	{
		mlx_put_image_to_window(
			data->mlx, data->win, data->imgs[next], 0, 0);
		data->img_ptr++;
	}
	else if (keycode == 65361 && data->imgs[prev])
	{
		mlx_put_image_to_window(
			data->mlx, data->win, data->imgs[prev], 0, 0);
		data->img_ptr--;
	}
	else
		return (0);
	return (1);
}

void	loop_gui(t_mlx_wrap *data)
{
	data->img_ptr = 1;
	mlx_put_image_to_window(
		data->mlx, data->win, data->imgs[data->img_ptr], 0, 0);
	mlx_hook(data->win, 17, 131072, w_close, data);
	mlx_hook(data->win, 2, 1, k_press, data);
	mlx_loop(data->mlx);
	free(data->imgs);
	free(data->addr);
	free(data);
}

t_mlx_wrap	*init_mlx_wrapper(t_scene *s)
{
	t_mlx_wrap	*data;
	// TODO wtf?
	// int screen_x;
	// int screen_y;
	data = malloc(sizeof(t_mlx_wrap));
	data->mlx = mlx_init();
	// mlx_get_screen_size(data->mlx, &screen_x, &screen_y);
	// if (s->resolution_x > screen_x)
	//     s->resolution_x = screen_x;
	// if (s->resolution_y > screen_y)
	//     s->resolution_y = screen_y;
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
