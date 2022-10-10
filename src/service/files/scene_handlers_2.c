/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/09/30 23:08:49 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

int	handle_c(char *line, t_scene *s, char *name)
{
	char	**input;
	t_tuple	*from;
	t_tuple	*dir;
	t_tuple	*up;
	double	fov;

	input = ft_whitespaces(line);
	free(line);
	if (input && ft_strequals(input[0], "c"))
	{
		from = get_tuple(input[1], 'p');
		dir = get_tuple(input[2], 'v');
		up = get_tuple(input[3], 'v');
		fov = ft_atoi(input[4]) * (M_PI / 180);
		s->cameras[s->camera_counter] = make_camera(
				s->resolution_y, s->resolution_x, fov, name, from);
		s->cameras[s->camera_counter]->transform = view_transform(
				tuple_copy(from),
				tuple_add(tuple_copy(from), dir),
				up);
		s->camera_counter++;
	}
	cleanup(input);
	return (1);
}

int	handle_l(char *line, t_scene *s)
{
	char	**input;
	t_tuple	*from;
	t_tuple	*color;
	double	brightness;

	input = ft_whitespaces(line);
	free(line);
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
	return (1);
}

int	handle_sphere(char **values, t_scene *s)
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
	return (1);
}

int	 handle_plane(char **values, t_scene *s)
{
	t_tuple		*coordinate;
	t_tuple		*norm;
	t_tuple		*color;
	t_matrix	*trans;

	coordinate = get_tuple(values[1], 'p');
	norm = get_tuple(values[2], 'v');
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
	return (1);
}
