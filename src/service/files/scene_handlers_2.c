/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/08/21 15:50:45 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	handle_c(char **input, t_scene *s)
{
	t_tuple		*dir;
	t_tuple		*up;
	t_camera	*cam;

	if (input && ft_strequals(input[0], "c"))
	{
		cam = make_camera(
				s->resolution_y,
				s->resolution_x,
				ft_atoi(input[4]) * (M_PI / 180));
		cam->from = get_tuple(input[1], 'p');
		dir = get_tuple(input[2], 'v');
		up = get_tuple(input[3], 'v');
		cam->transform = view_transform(
				tuple_copy(cam->from),
				tuple_add(tuple_copy(cam->from), dir),
				up);
		s->cameras[s->camera_counter] = cam;
		s->camera_counter++;
	}
	cleanup(input);
}

void	handle_l(char **input, t_scene *s)
{
	t_tuple	*from;
	t_tuple	*color;
	double	brightness;

	if (input && ft_strequals(input[0], "l"))
	{
		from = get_tuple(input[1], 'p');
		brightness = ft_atod(input[2]);
		color = tuple_scalar_multiply(get_tuple(input[3], 'c'),
				brightness * COLOR_CF);
		s->lights[s->light_counter] = light_make(from, color);
		s->light_counter++;
	}
	cleanup(input);
}

void	handle_sphere(char **values, t_scene *s)
{
	t_tuple	*centre;
	t_tuple	*color;
	double	diameter;

	centre = get_tuple(values[1], 'p');
	diameter = ft_atod(values[2]);
	color = tuple_scalar_multiply(
			get_tuple(values[3], 'c'), COLOR_CF);
	s->shapes[s->shape_counter] = make_shape('s',
			nsphere_unit(tuple_point(0, 0, 0)));
	s->shapes[s->shape_counter]->matrl = mat_with_col(color);
	set_transform(s->shapes[s->shape_counter], matrix_multiply(
			matrix_translate(centre->x, centre->y, centre->z),
			matrix_scale(
				diameter / 2, diameter / 2, diameter / 2)));
	tuple_free(centre);
	s->shape_counter++;
	cleanup(values);
}

void	print_tup(t_tuple *tup)
{
	printf("\tx:[%.2f], y:[%.2f], z:[%.2f]\n", tup->x, tup->y, tup->z);
}

void	handle_plane(char **values, t_scene *s)
{
	t_tuple		*coordinate;
	t_tuple		*norm;
	t_tuple		*color;
	t_matrix	*trans;

	coordinate = get_tuple(values[1], 'p');
	/* DEBUG */
	t_tuple		*tmp;
	tmp = get_tuple(values[2], 'v');
	print_tup(tmp);
	norm = tuple_normalize(get_tuple(values[2], 'v'));
	print_tup(norm);
	/* ***** */
	color = tuple_scalar_multiply(
			get_tuple(values[3], 'c'), COLOR_CF);
	s->shapes[s->shape_counter] = make_shape('p', plane_plane());
	s->shapes[s->shape_counter]->matrl = mat_with_col(color);
	s->shapes[s->shape_counter]->matrl->diffuse = 0.5;
	s->shapes[s->shape_counter]->matrl->ambient = 0.1;
	s->shapes[s->shape_counter]->matrl->specular = 0.1;
	s->shapes[s->shape_counter]->matrl->shininess = 50;
	if (norm->x == 0 && fabs(norm->y) == 1 && norm->z == 0)
		trans = matrix_identity(4);
	else
		trans = rotate_align(tuple_vector(0, 1, 0), norm);
	set_transform(s->shapes[s->shape_counter],
		matrix_multiply(matrix_translate(
				coordinate->x, coordinate->y, coordinate->z), trans));
	s->shape_counter++;
	cleanup(values);
}
