/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 14:12:05 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

bool	handle_c(char **input, t_scene *s)
{
	t_tmp		tmp;
	t_camera	*cam;

	if (input && ft_strequals(input[0], "c"))
	{
		cam = make_camera(
				s->res_y,
				s->res_x,
				ft_atoi(input[4]) * (M_PI / 180));
		set_tuple(&cam->from, input[1], 'p');
		set_tuple(&tmp.direct, input[2], 'v');
		set_tuple(&tmp.center, input[3], 'v');
		tuple_add(&tmp.tup, &cam->from, &tmp.direct);
		view_transform(&cam->transform, &cam->from, &tmp.tup, &tmp.center);
		s->cameras[s->camera_count] = cam;
		s->camera_count++;
	}
	return (true);
}

bool	handle_l(char **input, t_scene *s)
{
	t_tmp	tmp;
	t_light	*lt;

	if (input && ft_strequals(input[0], "l"))
	{
		set_tuple(&tmp.center, input[1], 'p');
		tmp.light_br = ft_atod(input[2]);
		set_tuple(&tmp.tup, input[3], 'c');
		tuple_scalar_multiply(&tmp.color, &tmp.tup, tmp.light_br * COLOR_CF);
		lt = (t_light *)malloc(sizeof(t_light));
		if (lt == NULL)
		{
			printf("Error: malloc fail in 'handle_l()'\n");
			return (cleanup(input), false);
		}
		light_make(lt, &tmp.center, &tmp.color);
		s->lights[s->light_count] = lt;
		s->light_count++;
	}
	return (true);
}

bool	handle_sphere(char **values, t_scene *s)
{
	t_tmp	tmp;

	set_tuple(&tmp.center, values[1], 'p');
	tmp.sph_d = ft_atod(values[2]);
	set_tuple(&tmp.tup, values[4], 'c');
	tuple_scalar_multiply(&tmp.color, &tmp.tup, COLOR_CF);
	tuple_point(&tmp.tup, 0, 0, 0);
	s->shapes[s->shape_count] = make_shape('s', nsphere_unit(&tmp.tup));
	mat_with_col(&s->shapes[s->shape_count]->matrl, &tmp.color);
	s->shapes[s->shape_count]->matrl.pattern = ft_atoi(values[3]);
	matrix_translate(&tmp.m, &tmp.center);
	tuple_point(&tmp.tup, tmp.sph_d / 2, tmp.sph_d / 2, tmp.sph_d / 2);
	matrix_scale(&tmp.m_cpy, &tmp.tup);
	matrix_multiply(&s->shapes[s->shape_count]->trans, &tmp.m, &tmp.m_cpy);
	s->shape_count++;
	return (true);
}

bool	handle_plane(char **values, t_scene *s)
{
	t_tmp	tmp;

	set_tuple(&tmp.center, values[1], 'p');
	set_tuple(&tmp.tup, values[2], 'v');
	tuple_normalize(&tmp.norm, &tmp.tup);
	set_tuple(&tmp.tup, values[4], 'c');
	tuple_scalar_multiply(&tmp.color, &tmp.tup, COLOR_CF);
	s->shapes[s->shape_count] = make_shape('p', plane_plane());
	mat_with_col(&s->shapes[s->shape_count]->matrl, &tmp.color);
	s->shapes[s->shape_count]->matrl.pattern = ft_atoi(values[3]);
	s->shapes[s->shape_count]->matrl.diffuse = 0.5;
	s->shapes[s->shape_count]->matrl.ambient = 0.1;
	s->shapes[s->shape_count]->matrl.specular = 0.1;
	s->shapes[s->shape_count]->matrl.shininess = 50;
	if (tmp.norm.x == 0 && fabs(tmp.norm.y) == 1 && tmp.norm.z == 0)
		matrix_identity(&tmp.trans, 4);
	else
	{
		tuple_vector(&tmp.tup, 0, 1, 0);
		rotate_align(&tmp.trans, &tmp.tup, &tmp.norm);
	}
	matrix_translate(&tmp.m, &tmp.center);
	matrix_multiply(&s->shapes[s->shape_count]->trans, &tmp.m, &tmp.trans);
	s->shape_count++;
	return (true);
}
