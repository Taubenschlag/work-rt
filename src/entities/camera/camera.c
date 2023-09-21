/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/21 18:40:32 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_camera	*make_camera(int h_s, int v_s, double fov)
{
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	cam->name = NULL;
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
	tuple_set(&tmp_p, ywrld, xwrld, -1);
	tuple_set(&tmp, 0.0, 0.0, 0.0);
	tuple_apply_trans_matrix(&pixel, &m_tmp->inv, &tmp_p);
	tuple_apply_trans_matrix(&r->origin, &m_tmp->inv, &tmp);
	tuple_substract(&tmp_p, &pixel, &r->origin);
	tuple_normalize(&r->dir, &tmp_p);
}

/*
** The t_tmp_m structure will contain the temp t_structs for computation
** also used in render() when saving the image in the file
** it is declared in matrix.h
*/
void	render(t_camera *c, t_world *w, t_canvas *img)
{
	t_tmp_m	m_tmp;
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