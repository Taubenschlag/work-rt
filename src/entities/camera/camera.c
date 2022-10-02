/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 16:55:28 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

s_camera	*make_camera(int h_s, int v_s, double fov, char *name, s_tuple *from)
{
	s_camera	*cam;

	cam = (s_camera *)malloc(sizeof(s_camera));
	cam->from = from;
	cam->name = name;
	cam->fov = fov;
	cam->h_size = h_s;
	cam->v_size = v_s;
	cam->transform = NULL;
	cam->half = tan(fov / 2);
	cam->aspect = (double)h_s / v_s;
	if (cam->aspect >= 1)
	{
		cam->half_w = cam->half;
		cam->half_h = cam->half / cam->aspect;
	}
	else
	{
		cam->half_w = cam->half * cam->aspect;
		cam->half_h = cam->half;
	}
	cam->pix_size = (cam->half_w * 2) / cam->h_size;
	return (cam);
}

void	free_camera(s_camera *c)
{
	matrix_free(c->transform);
	tuple_free(c->from);
	free(c);
}

s_ray	*ray_for_pix(s_camera *c, int y, int x)
{
	double	xwrld;
	double	ywrld;
	s_tuple	*pixel;
	s_tuple	*origin;
	s_tuple	*direction;

	xwrld = c->half_w - ((double)y + 0.5) * c->pix_size;
	ywrld = c->half_h - ((double)x + 0.5) * c->pix_size;
	pixel = tuple_apply_trans_matrix(
			matrix_invert(c->transform), tuple_point(ywrld, xwrld, -1));
	origin = tuple_apply_trans_matrix(
			matrix_invert(c->transform), tuple_point(0, 0, 0));
	direction = tuple_normalize(tuple_substract(pixel, tuple_copy(origin)));
	return (ray_ray(origin, direction));
}

s_canvas	*render(s_camera *c, s_world *w)
{
	s_canvas	*img;
	s_ray		*r;
	s_tuple		*color;
	int			y;
	int			x;

	img = canvas_canvas(c->v_size, c->h_size);
	y = -1;
	while (++y < c->h_size)
	{
		x = -1;
		while (++x < c->v_size)
		{
			r = ray_for_pix(c, y, x);
			color = color_at(w, r);
			ray_free(r);
			img->canvas[y][x] = tuple_to_rgb(color);
		}
	}
	return (img);
}
