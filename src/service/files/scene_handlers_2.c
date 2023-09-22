/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/22 13:53:11 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

typedef struct s_tmp
{
	double		diameter;
	t_tuple		center;
	t_tuple		color;
	t_tuple		tup;
	t_tuple		norm;
	t_matrix	m;
	t_matrix	m_scale;
	t_matrix	trans;
}	t_tmp;

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
		s->cameras[s->camera_count] = cam;
		s->camera_count++;
	}
	cleanup(input);
}

/*
** 1
** Allocated memory 
** implement protection 
** also must be freed in case of the following malloc errors
*/
bool	handle_l(char **input, t_scene *s)
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
		if (lt == NULL)
		{
			printf("Error: malloc fail in 'handle_l()'\n");
			return (cleanup(input), false);
		}
		light_make(lt, &from, &color);
		s->lights[s->light_count] = lt;
		s->light_count++;
	}
	return (cleanup(input), true);
}

/*
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
			cleanup(input);
		}
		light_make(lt, &from, &color);
		s->lights[s->light_counter] = lt;
		s->light_counter++;
	}
	cleanup(input);
}
*/
void	handle_sphere(char **values, t_scene *s)
{
	t_tmp	tmp;

	set_tuple(&tmp.center, values[1], 'p');
	tmp.diameter = ft_atod(values[2]);
	set_tuple(&tmp.tup, values[3], 'c');
	tuple_scalar_multiply(&tmp.color, &tmp.tup, COLOR_CF);
	tuple_point(&tmp.tup, 0, 0, 0);
	s->shapes[s->shape_count] = make_shape('s', nsphere_unit(&tmp.tup));
	mat_with_col(&s->shapes[s->shape_count]->matrl, &tmp.color);
	matrix_translate(&tmp.m, &tmp.center);
	tuple_point(&tmp.tup, tmp.diameter / 2, tmp.diameter / 2, tmp.diameter / 2);
	matrix_scale(&tmp.m_scale, &tmp.tup);
	matrix_multiply(&s->shapes[s->shape_count]->trans, &tmp.m, &tmp.m_scale);
	s->shape_count++;
	cleanup(values);
}

void	handle_plane(char **values, t_scene *s)
{
	t_tmp	tmp;

	set_tuple(&tmp.center, values[1], 'p');
	set_tuple(&tmp.tup, values[2], 'v');
	tuple_normalize(&tmp.norm, &tmp.tup);
	set_tuple(&tmp.tup, values[3], 'c');
	tuple_scalar_multiply(&tmp.color, &tmp.tup, COLOR_CF);
	s->shapes[s->shape_count] = make_shape('p', plane_plane());
	mat_with_col(&s->shapes[s->shape_count]->matrl, &tmp.color);
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
	cleanup(values);
}
