/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/22 13:52:38 by sbocanci         ###   ########.fr       */
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


void	handle_square_helper(t_tmp *tmp, t_square *sq, t_scene *s)
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
	//cleanup(values);
	return (free);	
}

void	handle_cylinder(char **values, t_scene *s)
{
	t_cylinder	*c;
	t_matrix	tmp_translate;
	t_matrix	tmp_m;
	t_matrix	tmp_mcp;
	t_tuple		tmp_tuple;

	s->shapes[s->shape_count] = make_shape(
			'y', cylinder_params(ft_atod(values[4])));
	c = (t_cylinder *)s->shapes[s->shape_count]->shape;
	set_tuple(&c->center, values[1], 'p');
	set_tuple(&tmp_tuple, values[2], 'v');
	tuple_normalize(&c->norm, &tmp_tuple);
	c->d = ft_atod(values[3]);
	set_tuple(&tmp_tuple, values[5], 'c');
	tuple_scalar_multiply(&c->color, &tmp_tuple, COLOR_CF);
	mat_with_col(&s->shapes[s->shape_count]->matrl, &c->color);
	if (fabs(c->norm.x) < 0000.1 && fabs(c->norm.y - 1.0) < 0000.1
		&& fabs(c->norm.z) < 0000.1)
	{
		matrix_identity(&c->trans, 4);
	}
	else
	{
		tuple_vector(&tmp_tuple, 0, 1, 0);
		rotate_align(&c->trans, &tmp_tuple, &c->norm);
	}
	matrix_translate(&tmp_m, &c->center);
	matrix_copy(&tmp_mcp, &c->trans);
	matrix_multiply(&tmp_translate, &tmp_m, &tmp_mcp);
	tmp_tuple.x = c->d / 2;
	tmp_tuple.y = 1;
	tmp_tuple.z = c->d / 2;
	matrix_scale(&tmp_m, &tmp_tuple);
	matrix_multiply(&s->shapes[s->shape_count]->trans, &tmp_translate, &tmp_m);
	s->shape_count++;
	cleanup(values);
}

void	handle_triangle(char **values, t_scene *s)
{
	t_triangle	*tr;
	t_tuple	a;
	t_tuple	b;
	t_tuple	c;
	t_tuple	color;
	t_tuple	tmp;

	set_tuple(&a, values[1], 'p');
	set_tuple(&b, values[2], 'p');
	set_tuple(&c, values[3], 'p');
	set_tuple(&tmp, values[4], 'c');
	tuple_scalar_multiply(&color, &tmp, COLOR_CF);
	tr = (t_triangle *)malloc(sizeof(t_triangle));
	if (tr == NULL)
	{
		//malloc error handling
	}
	triangle_coordinates(tr, &a, &b, &c);
	s->shapes[s->shape_count] = make_shape('i', tr);
	mat_with_col(&s->shapes[s->shape_count]->matrl, &color);
	s->shape_count++;
	cleanup(values);
}

void	handle_cone(char **values, t_scene *s)
{
	t_cone		*c;
	t_matrix	tmp_m_trans;
	t_matrix	tmp_m;
	t_tuple		tmp_tuple;

	s->shapes[s->shape_count] = make_shape('o',
			cone_param(ft_atod(values[4])));
	c = (t_cone *)s->shapes[s->shape_count]->shape;
	set_tuple(&c->center, values[1], 'p');

	set_tuple(&tmp_tuple, values[2], 'v');
	tuple_normalize(&c->norm, &tmp_tuple);
	c->d = ft_atod(values[3]);
	set_tuple(&tmp_tuple, values[5], 'c');
	tuple_scalar_multiply(&c->color, &tmp_tuple, COLOR_CF);
	mat_with_col(&s->shapes[s->shape_count]->matrl, &c->color);
	if (c->norm.x == 0 && fabs(c->norm.y) == 1 && c->norm.z == 0)
	{
		matrix_identity(&c->trans, 4);
	}
	else
	{
		tuple_vector(&tmp_tuple, 0, 1, 0);
		rotate_align(&c->trans, &tmp_tuple, &c->norm);
	}
	matrix_translate(&tmp_m, &c->center);
	matrix_multiply(&tmp_m_trans, &tmp_m, &c->trans);
	tmp_tuple.x = c->d / 2;
	tmp_tuple.y = 1;
	tmp_tuple.z = c->d / 2;
	matrix_scale(&tmp_m, &tmp_tuple);
	matrix_multiply(&s->shapes[s->shape_count]->trans, &tmp_m_trans, &tmp_m);
	s->shape_count++;
	cleanup(values);
}

void	handle_cube(char **values, t_scene *s)
{
	t_cube		*c;
	t_matrix	tmp_m_trans;
	t_matrix	tmp_m;
	t_tuple		tmp_tuple;
	t_tuple		tmp;

	s->shapes[s->shape_count] = make_shape('u', cube_cube());
	c = (t_cube *)s->shapes[s->shape_count]->shape;
	set_tuple(&c->center, values[1], 'p');
	set_tuple(&tmp_tuple, values[2], 'v');
	tuple_normalize(&c->norm, &tmp_tuple);
	c->side = ft_atod(values[3]);
	set_tuple(&tmp_tuple, values[4], 'c');
	tuple_scalar_multiply(&c->color, &tmp_tuple, COLOR_CF);
	mat_with_col(&s->shapes[s->shape_count]->matrl, &c->color);
	tuple_vector(&tmp_tuple, 1, 1, 0);
	tuple_normalize(&tmp, &tmp_tuple);
	if (tuple_equals(&c->norm, &tmp))
	{
		matrix_identity(&c->trans, 4);
	}
	else
	{
		tuple_vector(&tmp_tuple, 0, 1, 0);
		rotate_align(&c->trans, &tmp_tuple, &c->norm);
	}
	matrix_translate(&tmp_m, &c->center);
	matrix_multiply(&tmp_m_trans, &tmp_m, &c->trans);
	tmp_tuple.x = c->side / 2; 
	tmp_tuple.y = c->side / 2; 
	tmp_tuple.z = c->side / 2; 
	tmp_tuple.type = IS_POINT; // ??
	matrix_scale(&tmp_m, &tmp_tuple);
	matrix_multiply(&s->shapes[s->shape_count]->trans, &tmp_m, &tmp_m_trans);
	s->shape_count++;
	cleanup(values);
}
