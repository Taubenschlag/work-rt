/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 14:08:46 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

/*
** In this f() t_ray is created and used to project it through the objects.
** t_tuple *color is used to retrieve the color of each pixel
** and convert it to RGB before saving it on the canvas.
** 
** the t_tmp_m structure located in matrix.h
** contain the temp t_structs for intermediat computation
** also used in render() when saving the image in the file
*/
void	argb_render(t_camera *c, t_world *w, t_canvas *img)
{
	t_tmp_m		tmp;
	t_ray		ray;
	double		progress;

	init_canvas(c->v_size, c->h_size, img);
	tmp.y = -1;
	while (++tmp.y < c->h_size)
	{
		tmp.x = -1;
		while (++tmp.x < c->v_size)
		{
			ray_for_pix(c, &ray, &tmp);
			color_at(w, &ray, &tmp);
			img->canvas[tmp.y][tmp.x] = tuple_to_argb(&tmp.color);
			progress = ((tmp.y * c->v_size) + tmp.x) \
						/ (double)(c->h_size * c->v_size);
			display_progress(progress, c);
		}
	}
}

void	fill_image(t_canvas *c, t_mlx_wrap *data, int count)
{
	unsigned int	i;
	unsigned int	j;
	char			*dst;

	i = c->h;
	while (i > 0)
	{
		j = c->w;
		while (j > 0)
		{
			dst = data->addr[count] + ((i - 1) * data->line_length
					+ (j - 1) * (data->bits_per_pixel / 8));
			*(unsigned int *)dst = c->canvas[i - 1][j - 1];
			j--;
		}
		i--;
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
	if (data == NULL)
		return (NULL);
	data->mlx = mlx_init();
	data->imgs = malloc(sizeof(void *) * (s->camera_count + 2));
	data->addr = malloc(sizeof(char *) * (s->camera_count + 2));
	if (!data->mlx || !data->imgs || !data->addr)
		return (NULL);
	data->imgs[s->camera_count + 1] = NULL;
	data->imgs[0] = NULL;
	data->win = mlx_new_window(data->mlx, s->res_x, s->res_y, "miniRT");
	if (data->win == NULL)
		return (NULL);
	data->img_counter = s->camera_count;
	return (data);
}

bool	display_scene(t_scene *s)
{
	t_mlx_wrap	*data;
	t_canvas	c;
	t_world		w;
	int			cam;

	cam = 0;
	w.shape_counter = s->shape_count;
	init_world(&w, s->shapes, s->lights, s->light_count);
	data = init_mlx_wrapper(s);
	if (data == NULL)
		return (printf("Error initializing MLX\n"), false);
	while (++cam <= s->camera_count)
	{
		s->cameras[cam -1]->cam_count = cam - 1;
		s->cameras[cam -1]->cam_tot = s->camera_count;
		world_set_ambience(&w.amb, &s->cameras[cam - 1]->from, &s->ambi_color);
		argb_render(s->cameras[cam - 1], &w, &c);
		data->imgs[cam] = mlx_new_image(data->mlx, s->res_x, s->res_y);
		data->addr[cam] = mlx_get_data_addr(data->imgs[cam],
				&(data->bits_per_pixel), &(data->line_length), &(data->endian));
		fill_image(&c, data, cam);
		canvas_free(&c);
	}
	loop_gui(data);
	return (false);
}
