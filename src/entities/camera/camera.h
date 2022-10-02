/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 16:53:04 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "../../../heads_global/minirt.h"

typedef struct t_camera
{
	s_tuple		*from;
	char		*name;
	int			h_size;
	int			v_size;
	double		fov;
	double		pix_size;
	s_matrix	*transform;
	double		half;
	double		half_w;
	double		half_h;
	double		aspect;

}	s_camera;

// todo more than 4 args
s_camera	*make_camera(int h_size, int v_size, double fov,
				char *name, s_tuple *from);
s_ray		*ray_for_pix(s_camera *c, int y, int x);
s_canvas	*render(s_camera *c, s_world *w);
void		free_camera(s_camera *c);

#endif
