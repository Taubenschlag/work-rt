/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 11:20:49 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

static void	handle_square_helper(t_tmp *tmp, t_square *sq, t_scene *s)
{
	if (sq->norm.x == 0 && sq->norm.y == 0 && fabs(sq->norm.z) == 1)
		matrix_identity(&sq->trans, 4);
	else
	{
		tuple_vector(&tmp->tup, 0, 0, 1);
		rotate_align(&sq->trans, &tmp->tup, &sq->norm);
	}
	matrix_translate(&tmp->m, &sq->center);
	matrix_multiply(&tmp->trans, &tmp->m, &sq->trans);
	tuple_point(&tmp->center, sq->side, sq->side, sq->side);
	matrix_scale(&tmp->m, &tmp->center);
	matrix_multiply(&s->shapes[s->shape_count]->trans, &tmp->m, &tmp->trans);
	s->shape_count++;
}

bool	handle_square(char **values, t_scene *s)
{
	t_tmp		tmp;
	t_square	*sq;

	s->shapes[s->shape_count] = make_shape('q', square());
	if (s->shapes[s->shape_count] == NULL)
	{
		printf("Error: malloc fail in 'handle_square()'\n");
		return (false);
	}
	sq = (t_square *)s->shapes[s->shape_count]->shape;
	set_tuple(&sq->center, values[1], 'p');
	set_tuple(&tmp.tup, values[2], 'v');
	tuple_normalize(&sq->norm, &tmp.tup);
	sq->side = ft_atod(values[3]);
	set_tuple(&tmp.tup, values[4], 'c');
	tuple_scalar_multiply(&sq->color, &tmp.tup, COLOR_CF);
	mat_with_col(&s->shapes[s->shape_count]->matrl, &sq->color);
	handle_square_helper(&tmp, sq, s);
	return (true);
}

static void	handle_cylinder_helper(t_tmp *tmp, t_cylinder *c)
{
	if (fabs(c->norm.x) < 0000.1 && fabs(c->norm.y - 1.0) < 0000.1
		&& fabs(c->norm.z) < 0000.1)
	{
		matrix_identity(&c->trans, 4);
	}
	else
	{
		tuple_vector(&tmp->tup, 0, 1, 0);
		rotate_align(&c->trans, &tmp->tup, &c->norm);
	}
	matrix_translate(&tmp->m, &c->center);
	matrix_copy(&tmp->m_cpy, &c->trans);
	matrix_multiply(&tmp->trans, &tmp->m, &tmp->m_cpy);
	tuple_point(&tmp->tup, c->d / 2, 1, c->d / 2);
	matrix_scale(&tmp->m, &tmp->tup);
}

bool	handle_cylinder(char **values, t_scene *s)
{
	t_tmp		tmp;
	t_cylinder	*c;

	s->shapes[s->shape_count] = make_shape(
			'y', cylinder_params(ft_atod(values[4])));
	if (s->shapes[s->shape_count] == NULL)
	{
		printf("Error: malloc fail in 'handle_cylinder()'\n");
		return (false);
	}
	c = (t_cylinder *)s->shapes[s->shape_count]->shape;
	set_tuple(&c->center, values[1], 'p');
	set_tuple(&tmp.tup, values[2], 'v');
	tuple_normalize(&c->norm, &tmp.tup);
	c->d = ft_atod(values[3]);
	c->closed = ft_atoi(values[5]);
	set_tuple(&tmp.tup, values[6], 'c');
	tuple_scalar_multiply(&c->color, &tmp.tup, COLOR_CF);
	mat_with_col(&s->shapes[s->shape_count]->matrl, &c->color);
	handle_cylinder_helper(&tmp, c);
	matrix_multiply(&s->shapes[s->shape_count]->trans, &tmp.trans, &tmp.m);
	s->shape_count++;
	return (true);
}

bool	handle_triangle(char **values, t_scene *s)
{
	t_tmp		tmp;
	t_triangle	*tr;

	tr = (t_triangle *)malloc(sizeof(t_triangle));
	if (tr == NULL)
	{
		printf("Error: malloc fail in 'handle_triangle()'\n");
		return (false);
	}
	set_tuple(&tr->a, values[1], 'p');
	set_tuple(&tr->b, values[2], 'p');
	set_tuple(&tr->c, values[3], 'p');
	set_tuple(&tmp.tup, values[4], 'c');
	tuple_scalar_multiply(&tmp.color, &tmp.tup, COLOR_CF);
	triangle_coordinates(tr);
	s->shapes[s->shape_count] = make_shape('i', tr);
	mat_with_col(&s->shapes[s->shape_count]->matrl, &tmp.color);
	s->shape_count++;
	return (true);
}
