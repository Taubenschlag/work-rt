/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/14 22:04:35 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "../../../heads_global/minirt.h"

typedef struct camera
{
	t_tuple		*from;
	t_tuple		*up;
	char		*name;
	int			h_size;
	int			v_size;
	double		fov;
	double		pix_size;
	t_matrix	*transform;
	double		half;
	double		half_w;
	double		half_h;
	double		aspect;

}	t_camera;

// todo more than 4 args
t_camera	*make_camera(int h_size, int v_size, double fov,
				char *name, t_tuple *from);
t_ray		*ray_for_pix(t_camera *c, int y, int x);
t_canvas	*render(t_camera *c, t_world *w);
void		free_camera(t_camera *c);

#endif
