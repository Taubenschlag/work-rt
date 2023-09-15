/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/15 16:21:22 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_camera	*make_camera(int h_s, int v_s, double fov)
{
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	cam->h_size = h_s;
	cam->v_size = v_s;
	/* DEBUG */
	// need to initialize the instance of t_matrix
	//cam->transform = NULL;
	/* ***** */
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

void	free_camera(t_camera *c)
{
	//matrix_free(c->transform);
	tuple_free(c->from);
	free(c);
}

t_ray	*ray_for_pix(t_camera *c, int y, int x)
{
	double	xwrld;
	double	ywrld;
	t_tuple	*pixel;
	t_tuple	*origin;
	t_tuple	*direction;
	/**/
	t_tmp_m	m_tmp; // Initilizing first ??
	//t_matrix	inverted; // Initilizing first ??
	//t_matrix	cofactor; // Initilizing first ??

	/**/
	xwrld = c->half_w - ((double)y + 0.5) * c->pix_size;
	ywrld = c->half_h - ((double)x + 0.5) * c->pix_size;
	matrix_invert(&m_tmp, &c->transform);
	pixel = tuple_apply_trans_matrix(&m_tmp.inv, tuple_point(ywrld, xwrld, -1));
	origin = tuple_apply_trans_matrix(&m_tmp.inv, tuple_point(0, 0, 0));
	/* DEBUG 
	pixel = tuple_apply_trans_matrix(
			matrix_invert(c->transform), tuple_point(ywrld, xwrld, -1));
	origin = tuple_apply_trans_matrix(
			matrix_invert(c->transform), tuple_point(0, 0, 0));
	*/
	/* ***** */
	direction = tuple_normalize(tuple_substract(pixel, tuple_copy(origin)));
	return (ray_ray(origin, direction));
}

void	render(t_camera *c, t_world *w, t_canvas *img)
{
	/* DEBUG */
	// the following structure will contain the temp t_structs for computation
	//t_tmp_m	m_tmp; // located in matrix.h
	///////////
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
			img->canvas[y][x] = tuple_to_rgb(color);
		}
	}
}

/*
void	render(t_camera *c, t_world *w, t_canvas *img)
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
			img->canvas[y][x] = tuple_to_rgb(color);
		}
	}
}
*/