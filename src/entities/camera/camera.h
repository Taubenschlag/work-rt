/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/18 14:07:55 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "../../../heads_global/minirt.h"

typedef struct camera
{
	t_tuple		from;
	char		*name;
	int			h_size;
	int			v_size;
	double		pix_size;
	t_matrix	transform;
	double		half;
	double		half_w;
	double		half_h;
	double		aspect;

}	t_camera;

void		ray_for_pix(t_ray *r, t_camera *c, int y, int x, t_tmp_m *m_tmp);
t_camera	*make_camera(int h_s, int v_s, double fov);
void		render(t_camera *c, t_world *w, t_canvas *img);
void		free_camera(t_camera *c);

#endif
