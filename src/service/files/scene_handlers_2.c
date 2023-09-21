/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/21 18:41:02 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	handle_c(char **input, t_scene *s)
{
	t_tuple		dir;
	t_tuple		up;
	t_tuple		tmp;
	t_camera	*cam;

	if (input && ft_strequals(input[0], "c"))
	{
		cam = make_camera(
				s->resolution_y,
				s->resolution_x,
				ft_atoi(input[4]) * (M_PI / 180));
		set_tuple(&cam->from, input[1], 'p');
		set_tuple(&dir, input[2], 'v');
		set_tuple(&up, input[3], 'v');
		tuple_add(&tmp, &cam->from, &dir);
		view_transform(&cam->transform, &cam->from, &tmp, &up);
		s->cameras[s->camera_counter] = cam;
		s->camera_counter++;
	}
	cleanup(input);
}

void	handle_l(char **input, t_scene *s)
{
	t_light	*lt;
	t_tuple	from;
	t_tuple	color;
	t_tuple	tmp;
	double	brightness;

	if (input && ft_strequals(input[0], "l"))
	{
		set_tuple(&from, input[1], 'p');
		brightness = ft_atod(input[2]);

		set_tuple(&tmp, input[3], 'c');
		tuple_scalar_multiply(&color, &tmp, brightness * COLOR_CF);

		lt = (t_light *)malloc(sizeof(t_light));
		{
			//malloc error handling
		}
		light_make(lt, &from, &color);
		s->lights[s->light_counter] = lt;
		s->light_counter++;
	}
	cleanup(input);
}

void	handle_sphere(char **values, t_scene *s)
{
	t_tuple	centre;
	t_tuple	color;
	double	diameter;
	t_matrix	tmp_m;
	t_matrix	tmp_m_scale;
	t_tuple		tmp_tuple;

	set_tuple(&centre, values[1], 'p');
	diameter = ft_atod(values[2]);
	set_tuple(&tmp_tuple, values[3], 'c');
	tuple_scalar_multiply(&color, &tmp_tuple, COLOR_CF);
	tuple_point(&tmp_tuple, 0, 0, 0);
	s->shapes[s->shape_counter] = make_shape('s', nsphere_unit(&tmp_tuple));
	mat_with_col(&s->shapes[s->shape_counter]->matrl, &color); 
	matrix_translate(&tmp_m, &centre);
	tuple_point(&tmp_tuple, diameter / 2, diameter / 2, diameter / 2);
	matrix_scale(&tmp_m_scale, &tmp_tuple);
	matrix_multiply(&s->shapes[s->shape_counter]->trans, &tmp_m, &tmp_m_scale);
	s->shape_counter++;
	cleanup(values);
}

void	handle_plane(char **values, t_scene *s)
{
	t_tuple		coordinate;
	t_tuple		norm;
	t_tuple		color;
	t_tuple		tmp;
	t_matrix	trans;
	t_matrix	tmp_m;

	set_tuple(&coordinate, values[1], 'p');
	set_tuple(&tmp, values[2], 'v');
	tuple_normalize(&norm, &tmp);
	set_tuple(&tmp, values[3], 'c');
	tuple_scalar_multiply(&color, &tmp, COLOR_CF);
	s->shapes[s->shape_counter] = make_shape('p', plane_plane());
	mat_with_col(&s->shapes[s->shape_counter]->matrl, &color);
	s->shapes[s->shape_counter]->matrl.diffuse = 0.5;
	s->shapes[s->shape_counter]->matrl.ambient = 0.1;
	s->shapes[s->shape_counter]->matrl.specular = 0.1;
	s->shapes[s->shape_counter]->matrl.shininess = 50;
	if (norm.x == 0 && fabs(norm.y) == 1 && norm.z == 0)
	{
		matrix_identity(&trans, 4);
	}
	else
	{
		tuple_vector(&tmp, 0, 1, 0);
		rotate_align(&trans, &tmp, &norm);
	}
	matrix_translate(&tmp_m, &coordinate);
	matrix_multiply(&s->shapes[s->shape_counter]->trans, &tmp_m, &trans);
	s->shape_counter++;
	cleanup(values);
}
