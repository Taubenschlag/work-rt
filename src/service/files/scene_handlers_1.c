/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/09/30 23:16:03 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

//TODO func more than 25
int	handle_square(char **values, s_scene *s)
{
	s_tuple		*center;
	s_tuple		*norm;
	s_tuple		*color;
	s_matrix	*trans;
	double		side;

	center = get_tuple(values[1], 'p');
	norm = tuple_normalize(get_tuple(values[2], 'v'));
	side = ft_atod(values[3]);
	color = tuple_scalar_multiply(get_tuple(values[4], 'c'),
			COLOR_CF);
	s->shapes[s->shape_counter] = make_shape('q', square());
	s->shapes[s->shape_counter]->matrl = mat_with_col(color);
	if (norm->x == 0 && norm->y == 0 && fabs(norm->z) == 1)
		trans = matrix_identity(4);
	else
		trans = rotate_align(tuple_vector(0, 0, 1), norm);
	tuple_free(norm);
	trans = matrix_multiply(matrix_translate(center->x, center->y, center->z),
			trans);
	trans = matrix_multiply(matrix_scale(side, side, side), trans);
	set_transform(s->shapes[s->shape_counter], trans);
	s->shape_counter++;
	cleanup(values);
	free(center);
	return (1);
}

//TODO too much variables
//TODO func more than 25
int	handle_cylinder(char **values, s_scene *s)
{
	s_tuple		*center;
	s_tuple		*norm;
	s_tuple		*color;
	s_matrix	*trans;
	double		d;
	double		h;

	center = get_tuple(values[1], 'p');
	norm = tuple_normalize(get_tuple(values[2], 'v'));
	d = ft_atod(values[3]);
	h = ft_atod(values[4]);
	color = tuple_scalar_multiply(get_tuple(values[5], 'c'),
			COLOR_CF);
	s->shapes[s->shape_counter] = make_shape('y', cylinder_params(h));
	s->shapes[s->shape_counter]->matrl = mat_with_col(color);
	if (fabs(norm->x) < 0000.1 && fabs(norm->y - 1.0) < 0000.1 && fabs(norm->z) < 0000.1)
		trans = matrix_identity(4);
	else
		trans = rotate_align(tuple_vector(0, 1, 0), norm);
	tuple_free(norm);
	trans = matrix_multiply(matrix_translate(center->x, center->y, center->z),
			trans);
	tuple_free(center);
	trans = matrix_multiply(trans, matrix_scale(d / 2, 1, d / 2));
	set_transform(s->shapes[s->shape_counter], trans);
	s->shape_counter++;
	cleanup(values);
	return (1);
}

int	handle_triangle(char **values, s_scene *s)
{
	s_tuple	*a;
	s_tuple	*b;
	s_tuple	*c;
	s_tuple	*color;

	a = get_tuple(values[1], 'p');
	b = get_tuple(values[2], 'p');
	c = get_tuple(values[3], 'p');
	color = tuple_scalar_multiply(get_tuple(values[4], 'c'), COLOR_CF);
	s->shapes[s->shape_counter] = make_shape(
			'i', triangle_coordinates(a, b, c));
	s->shapes[s->shape_counter]->matrl = mat_with_col(color);
	s->shape_counter++;
	cleanup(values);
	return (1);
}

//TODO func more than 25
int	handle_cone(char **values, s_scene *s)
{
	s_tuple		*center;
	s_tuple		*norm;
	s_tuple		*color;
	s_matrix	*trans;
	double		p[2];

	center = get_tuple(values[1], 'p');
	norm = tuple_normalize(get_tuple(values[2], 'v'));
	p[0] = ft_atod(values[3]);
	p[1] = ft_atod(values[4]);
	color = tuple_scalar_multiply(get_tuple(values[5], 'c'), COLOR_CF);
	s->shapes[s->shape_counter] = make_shape('o', cone_param(p[1]));
	s->shapes[s->shape_counter]->matrl = mat_with_col(color);
	if (norm->x == 0 && fabs(norm->y) == 1 && norm->z == 0)
		trans = matrix_identity(4);
	else
		trans = rotate_align(tuple_vector(0, 1, 0), norm);
	tuple_free(norm);
	trans = matrix_multiply(
			matrix_translate(center->x, center->y, center->z), trans);
	tuple_free(center);
	trans = matrix_multiply(trans, matrix_scale(p[0] / 2, 1, p[0] / 2));
	set_transform(s->shapes[s->shape_counter], trans);
	s->shape_counter++;
	cleanup(values);
	return (1);
}

//TODO func more than 25
int	handle_cube(char **values, s_scene *s)
{
	s_tuple		*center;
	double		side;
	s_tuple		*color;
	s_tuple		*norm;
	s_matrix	*trans;

	center = get_tuple(values[1], 'p');
	norm = tuple_normalize(get_tuple(values[2], 'v'));
	side = ft_atod(values[3]);
	color = tuple_scalar_multiply(
			get_tuple(values[4], 'c'), COLOR_CF);
	s->shapes[s->shape_counter] = make_shape('u', cube_cube());
	s->shapes[s->shape_counter]->matrl = mat_with_col(color);
	if (tuple_equals(tuple_copy(norm), tuple_normalize(tuple_vector(1, 1, 0))))
		trans = matrix_identity(4);
	else
		trans = rotate_align(tuple_vector(0, 1, 0), norm);
	trans = matrix_multiply(matrix_translate(
				center->x, center->y, center->z), trans);
	trans = matrix_multiply(matrix_scale(side / 2, side / 2, side / 2), trans);
	set_transform(s->shapes[s->shape_counter], trans);
	s->shape_counter++;
	free(center);
	free(norm);
	cleanup(values);
	return (1);
}
