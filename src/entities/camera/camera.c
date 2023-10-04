/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 14:55:12 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_camera	*make_camera(int h_s, int v_s, double fov)
{
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (cam == NULL)
		return (NULL);
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

void	ray_for_pix(t_camera *c, t_ray *ray, t_tmp_m *m_tmp)
{
	double	xwrld;
	double	ywrld;
	t_tuple	pixel;
	t_tuple	tmp;
	t_tuple	tmp_p;

	xwrld = c->half_w - ((double)m_tmp->y + 0.5) * c->pix_size;
	ywrld = c->half_h - ((double)m_tmp->x + 0.5) * c->pix_size;
	matrix_invert(m_tmp, &c->transform);
	tuple_set(&tmp_p, ywrld, xwrld, -1);
	tuple_set(&tmp, 0.0, 0.0, 0.0);
	tuple_apply_trans_matrix(&pixel, &m_tmp->inv, &tmp_p);
	tuple_apply_trans_matrix(&ray->origin, &m_tmp->inv, &tmp);
	tuple_substract(&tmp_p, &pixel, &ray->origin);
	tuple_normalize(&ray->dir, &tmp_p);
}

/*
** The t_tmp_m structure will contain the temp t_structs for computation
** also used in render() when saving the image in the file
** it is declared in matrix.h
*/
bool	render(t_camera *c, t_world *w, t_canvas *img)
{
	t_tmp_m	tmp;
	t_ray	ray;
	double	progress;

	if (img->canvas == NULL)
	{
		printf("Error allocating memory for canvas\n");
		return (false);
	}
	tmp.y = -1;
	while (++tmp.y < c->h_size)
	{
		tmp.x = -1;
		while (++tmp.x < c->v_size)
		{
			ray_for_pix(c, &ray, &tmp);
			color_at(w, &ray, &tmp);
			img->canvas[tmp.y][tmp.x] = tuple_to_rgb(&tmp.color);
			progress = ((tmp.y * c->v_size) + tmp.x) \
							/ ((double)c->h_size * c->v_size);
			display_progress(progress, c);
		}
	}
	return (true);
}

void	display_progress(double progress, t_camera *cam)
{
	int	bar;
	int	width;
	int	i;

	bar = 50;
	width = bar * progress;
	printf("RENDERING SCENE: %d/%d [", cam->cam_count + 1, cam->cam_tot);
	i = 0;
	while (i < bar)
	{
		if (i <= width)
			printf("+");
		else
			printf(" ");
		i++;
	}
	printf("] \r");
	fflush(stdout);
}
