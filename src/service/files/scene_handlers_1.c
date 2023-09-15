/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/15 18:32:52 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	handle_square(char **values, t_scene *s)
{
	// DEBUG
	//printf("SQUARE\n");
	//
	t_square	*sq;
	/**/
	t_matrix	tmp_m_trans;
	t_matrix	tmp_m;
	t_tuple		tmp_tuple;

	s->shapes[s->shape_counter] = make_shape('q', square());
	sq = (t_square *)s->shapes[s->shape_counter]->shape;
	sq->center = get_tuple(values[1], 'p');
	sq->norm = tuple_normalize(get_tuple(values[2], 'v'));
	sq->side = ft_atod(values[3]);
	sq->color = tuple_scalar_multiply(get_tuple(values[4], 'c'),
			COLOR_CF);
	s->shapes[s->shape_counter]->matrl = mat_with_col(sq->color);
	if (sq->norm->x == 0 && sq->norm->y == 0 && fabs(sq->norm->z) == 1)
	{
		matrix_identity(&sq->trans, 4);
		//sq->trans = matrix_identity(4);
	}
	else
		rotate_align(&sq->trans, tuple_vector(0, 0, 1), sq->norm);
		//sq->trans = rotate_align(tuple_vector(0, 0, 1), sq->norm);
	tuple_free(sq->norm);
	/* DEBUG 
	sq->trans = matrix_multiply(matrix_translate(
				sq->center->x, sq->center->y, sq->center->z), sq->trans);
	sq->trans = matrix_multiply(matrix_scale(
				sq->side, sq->side, sq->side), sq->trans);
	*/
	matrix_translate(&tmp_m, sq->center);
	matrix_multiply(&tmp_m_trans, &tmp_m, &sq->trans);
	tmp_tuple.x = sq->side;
	tmp_tuple.y = sq->side;
	tmp_tuple.z = sq->side;
	matrix_scale(&tmp_m, &tmp_tuple);
	//matrix_multiply(&sq->trans, &tmp_m, &tmp_m_trans);
	matrix_multiply(&s->shapes[s->shape_counter]->trans, &tmp_m, &tmp_m_trans);
	//set_transform(s->shapes[s->shape_counter], sq->trans);
	/* ***** */
	s->shape_counter++;
	cleanup(values);
	free(sq->center);
}

void	handle_cylinder(char **values, t_scene *s)
{
	// DEBUG
	//printf("CYLINDER\n");
	//
	t_cylinder	*c;
	/**/
	t_matrix	tmp_translate;
	t_matrix	tmp_m;
	t_matrix	tmp_mcp;
	t_tuple		tmp_tuple;

	/**/
	s->shapes[s->shape_counter] = make_shape(
			'y', cylinder_params(ft_atod(values[4])));
	c = (t_cylinder *)s->shapes[s->shape_counter]->shape;
	c->center = get_tuple(values[1], 'p');
	c->norm = tuple_normalize(get_tuple(values[2], 'v'));
	c->d = ft_atod(values[3]);
	c->color = tuple_scalar_multiply(get_tuple(values[5], 'c'),
			COLOR_CF);
	s->shapes[s->shape_counter]->matrl = mat_with_col(c->color);
	if (fabs(c->norm->x) < 0000.1
		&& fabs(c->norm->y - 1.0) < 0000.1 && fabs(c->norm->z) < 0000.1)
	{
		//c->trans = matrix_identity(4);
		matrix_identity(&c->trans, 4);
	}
	else
		rotate_align(&c->trans, tuple_vector(0, 1, 0), c->norm);
		//c->trans = rotate_align(tuple_vector(0, 1, 0), c->norm);
	tuple_free(c->norm);
	/* DEBUG 
	c->trans = matrix_multiply(matrix_translate(c->center->x, c->center->y, c->center->z), c->trans);
	*/
	matrix_translate(&tmp_m, c->center);
	matrix_copy(&tmp_mcp, &c->trans);
	matrix_multiply(&tmp_translate, &tmp_m, &tmp_mcp);
	tuple_free(c->center);
	//c->trans = matrix_multiply(c->trans, matrix_scale(c->d / 2, 1, c->d / 2));
	tmp_tuple.x = c->d / 2;
	tmp_tuple.y = 1;
	tmp_tuple.z = c->d / 2;
	matrix_scale(&tmp_m, &tmp_tuple);
	//matrix_multiply(&c->trans, &tmp_translate, &tmp_m);
	matrix_multiply(&s->shapes[s->shape_counter]->trans, &tmp_translate, &tmp_m);
	//set_transform(s->shapes[s->shape_counter], &c->trans);
	/* ***** */
	s->shape_counter++;
	cleanup(values);
}

void	handle_triangle(char **values, t_scene *s)
{
	// DEBUG
	//printf("TRIANGLE\n");
	//
	t_tuple	*a;
	t_tuple	*b;
	t_tuple	*c;
	t_tuple	*color;

	a = get_tuple(values[1], 'p');
	b = get_tuple(values[2], 'p');
	c = get_tuple(values[3], 'p');
	color = tuple_scalar_multiply(get_tuple(values[4], 'c'), COLOR_CF);
	s->shapes[s->shape_counter] = make_shape(
			'i', triangle_coordinates(a, b, c));
	s->shapes[s->shape_counter]->matrl = mat_with_col(color);
	s->shape_counter++;
	cleanup(values);
}

void	handle_cone(char **values, t_scene *s)
{
	// DEBUG
	//printf("CONE\n");
	//
	t_cone		*c;
	/**/
	t_matrix	tmp_m_trans;
	t_matrix	tmp_m;
	t_tuple		tmp_tuple;

	/**/
	s->shapes[s->shape_counter] = make_shape('o',
			cone_param(ft_atod(values[4])));
	c = (t_cone *)s->shapes[s->shape_counter]->shape;
	c->center = get_tuple(values[1], 'p');
	c->norm = tuple_normalize(get_tuple(values[2], 'v'));
	c->d = ft_atod(values[3]);
	c->color = tuple_scalar_multiply(get_tuple(values[5], 'c'), COLOR_CF);
	s->shapes[s->shape_counter]->matrl = mat_with_col(c->color);
	if (c->norm->x == 0 && fabs(c->norm->y) == 1 && c->norm->z == 0)
	{
		//c->trans = matrix_identity(4);
		matrix_identity(&c->trans, 4);
	}
	else
		rotate_align(&c->trans, tuple_vector(0, 1, 0), c->norm);
		//c->trans = rotate_align(tuple_vector(0, 1, 0), c->norm);
	tuple_free(c->norm);
	/* DEBUG 
	c->trans = matrix_multiply(matrix_translate(c->center->x, c->center->y, c->center->z), c->trans);
	*/
	matrix_translate(&tmp_m, c->center);
	matrix_multiply(&tmp_m_trans, &tmp_m, &c->trans);
	tuple_free(c->center);
	//c->trans = matrix_multiply(c->trans, matrix_scale(c->d / 2, 1, c->d / 2));
	tmp_tuple.x = c->d / 2;
	tmp_tuple.y = 1;
	tmp_tuple.z = c->d / 2;
	matrix_scale(&tmp_m, &tmp_tuple);
	//matrix_multiply(&c->trans, &tmp_m_trans, &tmp_m);
	matrix_multiply(&s->shapes[s->shape_counter]->trans, &tmp_m_trans, &tmp_m);
	//set_transform(s->shapes[s->shape_counter], &c->trans);
	/* ***** */
	s->shape_counter++;
	cleanup(values);
}

void	handle_cube(char **values, t_scene *s)
{
	// DEBUG
	//printf("CUBE\n");
	//
	t_cube		*c;
	/**/
	t_matrix	tmp_m_trans;
	t_matrix	tmp_m;
	t_tuple		tmp_tuple;

	/**/
	s->shapes[s->shape_counter] = make_shape('u', cube_cube());
	c = (t_cube *)s->shapes[s->shape_counter]->shape;
	c->center = get_tuple(values[1], 'p');
	c->norm = tuple_normalize(get_tuple(values[2], 'v'));
	c->side = ft_atod(values[3]);
	c->color = tuple_scalar_multiply(
			get_tuple(values[4], 'c'), COLOR_CF);
	s->shapes[s->shape_counter]->matrl = mat_with_col(c->color);
	if (tuple_equals(tuple_copy(c->norm),
			tuple_normalize(tuple_vector(1, 1, 0))))
	{
		//c->trans = matrix_identity(4);
		matrix_identity(&c->trans, 4);
	}
	else
		rotate_align(&c->trans, tuple_vector(0, 1, 0), c->norm);
		//c->trans = rotate_align(tuple_vector(0, 1, 0), c->norm);
	/* DEBUG 
	c->trans = matrix_multiply(matrix_translate(
				c->center->x, c->center->y, c->center->z), c->trans);
	c->trans = matrix_multiply(matrix_scale(
				c->side / 2, c->side / 2, c->side / 2), c->trans);
	*/
	matrix_translate(&tmp_m, c->center);
	matrix_multiply(&tmp_m_trans, &tmp_m, &c->trans);
	tmp_tuple.x = c->side / 2; 
	tmp_tuple.y = c->side / 2; 
	tmp_tuple.z = c->side / 2; 
	matrix_scale(&tmp_m, &tmp_tuple);
	//matrix_multiply(&c->trans, &tmp_m, &tmp_m_trans);
	matrix_multiply(&s->shapes[s->shape_counter]->trans, &tmp_m, &tmp_m_trans);
	//set_transform(s->shapes[s->shape_counter], &c->trans);
	/* ***** */
	s->shape_counter++;
	free(c->center);
	free(c->norm);
	cleanup(values);
}
/*
void	handle_square(char **values, t_scene *s)
{
	t_square	*sq;

	s->shapes[s->shape_counter] = make_shape('q', square());
	sq = (t_square *)s->shapes[s->shape_counter]->shape;
	sq->center = get_tuple(values[1], 'p');
	sq->norm = tuple_normalize(get_tuple(values[2], 'v'));
	sq->side = ft_atod(values[3]);
	sq->color = tuple_scalar_multiply(get_tuple(values[4], 'c'),
			COLOR_CF);
	s->shapes[s->shape_counter]->matrl = mat_with_col(sq->color);
	if (sq->norm->x == 0 && sq->norm->y == 0 && fabs(sq->norm->z) == 1)
		sq->trans = matrix_identity(4);
	else
		sq->trans = rotate_align(tuple_vector(0, 0, 1), sq->norm);
	tuple_free(sq->norm);
	sq->trans = matrix_multiply(matrix_translate(
				sq->center->x, sq->center->y, sq->center->z), sq->trans);
	sq->trans = matrix_multiply(matrix_scale(
				sq->side, sq->side, sq->side), sq->trans);
	set_transform(s->shapes[s->shape_counter], sq->trans);
	s->shape_counter++;
	cleanup(values);
	free(sq->center);
}

void	handle_cylinder(char **values, t_scene *s)
{
	t_cylinder	*c;

	s->shapes[s->shape_counter] = make_shape(
			'y', cylinder_params(ft_atod(values[4])));
	c = (t_cylinder *)s->shapes[s->shape_counter]->shape;
	c->center = get_tuple(values[1], 'p');
	c->norm = tuple_normalize(get_tuple(values[2], 'v'));
	c->d = ft_atod(values[3]);
	c->color = tuple_scalar_multiply(get_tuple(values[5], 'c'),
			COLOR_CF);
	s->shapes[s->shape_counter]->matrl = mat_with_col(c->color);
	if (fabs(c->norm->x) < 0000.1
		&& fabs(c->norm->y - 1.0) < 0000.1 && fabs(c->norm->z) < 0000.1)
		c->trans = matrix_identity(4);
	else
		c->trans = rotate_align(tuple_vector(0, 1, 0), c->norm);
	tuple_free(c->norm);
	c->trans = matrix_multiply(matrix_translate(
				c->center->x, c->center->y, c->center->z), c->trans);
	tuple_free(c->center);
	c->trans = matrix_multiply(c->trans, matrix_scale(c->d / 2, 1, c->d / 2));
	set_transform(s->shapes[s->shape_counter], c->trans);
	s->shape_counter++;
	cleanup(values);
}

void	handle_triangle(char **values, t_scene *s)
{
	t_tuple	*a;
	t_tuple	*b;
	t_tuple	*c;
	t_tuple	*color;

	a = get_tuple(values[1], 'p');
	b = get_tuple(values[2], 'p');
	c = get_tuple(values[3], 'p');
	color = tuple_scalar_multiply(get_tuple(values[4], 'c'), COLOR_CF);
	s->shapes[s->shape_counter] = make_shape(
			'i', triangle_coordinates(a, b, c));
	s->shapes[s->shape_counter]->matrl = mat_with_col(color);
	s->shape_counter++;
	cleanup(values);
}

void	handle_cone(char **values, t_scene *s)
{
	t_cone		*c;

	s->shapes[s->shape_counter] = make_shape('o',
			cone_param(ft_atod(values[4])));
	c = (t_cone *)s->shapes[s->shape_counter]->shape;
	c->center = get_tuple(values[1], 'p');
	c->norm = tuple_normalize(get_tuple(values[2], 'v'));
	c->d = ft_atod(values[3]);
	c->color = tuple_scalar_multiply(get_tuple(values[5], 'c'), COLOR_CF);
	s->shapes[s->shape_counter]->matrl = mat_with_col(c->color);
	if (c->norm->x == 0 && fabs(c->norm->y) == 1 && c->norm->z == 0)
		c->trans = matrix_identity(4);
	else
		c->trans = rotate_align(tuple_vector(0, 1, 0), c->norm);
	tuple_free(c->norm);
	c->trans = matrix_multiply(matrix_translate(
				c->center->x, c->center->y, c->center->z), c->trans);
	tuple_free(c->center);
	c->trans = matrix_multiply(c->trans, matrix_scale(c->d / 2, 1, c->d / 2));
	set_transform(s->shapes[s->shape_counter], c->trans);
	s->shape_counter++;
	cleanup(values);
}

void	handle_cube(char **values, t_scene *s)
{
	t_cube		*c;

	s->shapes[s->shape_counter] = make_shape('u', cube_cube());
	c = (t_cube *)s->shapes[s->shape_counter]->shape;
	c->center = get_tuple(values[1], 'p');
	c->norm = tuple_normalize(get_tuple(values[2], 'v'));
	c->side = ft_atod(values[3]);
	c->color = tuple_scalar_multiply(
			get_tuple(values[4], 'c'), COLOR_CF);
	s->shapes[s->shape_counter]->matrl = mat_with_col(c->color);
	if (tuple_equals(tuple_copy(c->norm),
			tuple_normalize(tuple_vector(1, 1, 0))))
		c->trans = matrix_identity(4);
	else
		c->trans = rotate_align(tuple_vector(0, 1, 0), c->norm);
	c->trans = matrix_multiply(matrix_translate(
				c->center->x, c->center->y, c->center->z), c->trans);
	c->trans = matrix_multiply(matrix_scale(
				c->side / 2, c->side / 2, c->side / 2), c->trans);
	set_transform(s->shapes[s->shape_counter], c->trans);
	s->shape_counter++;
	free(c->center);
	free(c->norm);
	cleanup(values);
}
*/