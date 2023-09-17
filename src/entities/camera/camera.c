/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 22:12:28 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

/* DEBUG */
void	print_camera(t_camera *cam)
{
	printf("\t\t=========================\n");
	printf("\t\tCAMERA\n");
	printf("\t\ttuple from:");
	print_tuple(&cam->from);
	printf("\t\tname:[%s]\n", cam->name);
	printf("\t\tsize h:[%d], v:[%d], pix_size:[%.2f]\n", cam->h_size, cam->v_size, cam->pix_size);
	printf("\t\ttransform:\n");
	print_matrix(&cam->transform);
	printf("\t\thalf:[%.2f], h_w:[%.2f], h_h:[%.2f], aspect:[%.2f]\n", cam->half, cam->half_w, cam->half_h, cam->aspect);
	printf("\t\t= = = = = = = = = = = = =\n");
}
/* ***** */

t_camera	*make_camera(int h_s, int v_s, double fov)
{
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	cam->h_size = h_s;
	cam->v_size = v_s;
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

void	ray_for_pix(t_ray *r, t_camera *c, int y, int x, t_tmp_m *m_tmp)
{
	double	xwrld;
	double	ywrld;
	t_tuple	pixel;
	t_tuple	tmp;
	t_tuple	tmp_p;

	xwrld = c->half_w - ((double)y + 0.5) * c->pix_size;
	ywrld = c->half_h - ((double)x + 0.5) * c->pix_size;
	matrix_invert(m_tmp, &c->transform);
	tuple_set(&tmp_p, xwrld, ywrld, -1);
	tuple_set(&tmp, 0, 0, 0);
	tuple_apply_trans_matrix(&pixel, &m_tmp->inv, &tmp_p);
	tuple_apply_trans_matrix(&r->origin, &m_tmp->inv, &tmp);
	tuple_substract(&tmp_p, &pixel, &r->origin);
	tuple_normalize(&r->dir, &tmp_p);
}

void	render(t_camera *c, t_world *w, t_canvas *img)
{
	/* DEBUG */
	// the following structure will contain the temp t_structs for computation
	// also used in render() when saving the image in the file
	t_tmp_m	m_tmp; // located in matrix.h
	///////////
	t_ray		r;
	int			y;
	int			x;

	init_canvas(c->v_size, c->h_size, img);
	y = -1;
	while (++y < c->h_size)
	{
		x = -1;
		while (++x < c->v_size)
		{
			ray_for_pix(&r, c, y, x, &m_tmp);
			color_at(w, &r, &m_tmp);
			img->canvas[y][x] = tuple_to_rgb(&m_tmp.color);
		}
	}
}

void		free_camera(t_camera *c)
{
	if (c)
	{
		if (c->name)
			free(c->name);
		free(c);
	}
}