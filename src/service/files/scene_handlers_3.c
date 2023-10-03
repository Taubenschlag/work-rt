/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handlers_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/23 13:27:13 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

static void	handle_cone_helper(t_tmp *tmp, t_cone *c)
{
	if (c->norm.x == 0 && fabs(c->norm.y) == 1 && c->norm.z == 0)
	{
		matrix_identity(&c->trans, 4);
	}
	else
	{
		tuple_vector(&tmp->tup, 0, 1, 0);
		rotate_align(&c->trans, &tmp->tup, &c->norm);
	}
	matrix_translate(&tmp->m, &c->center);
	matrix_multiply(&tmp->trans, &tmp->m, &c->trans);
	tuple_point(&tmp->tup, c->d / 2, 1, c->d / 2);
	matrix_scale(&tmp->m, &tmp->tup);
}

bool	handle_cone(char **values, t_scene *s)
{
	t_tmp	tmp;
	t_cone	*c;

	s->shapes[s->shape_count] = make_shape('o',
			cone_param(ft_atod(values[4])));
	if (s->shapes[s->shape_count] == NULL)
	{
		printf("Error: malloc fail in 'handle_cone()'\n");
		return (false);
	}
	c = (t_cone *)s->shapes[s->shape_count]->shape;
	set_tuple(&c->center, values[1], 'p');
	set_tuple(&tmp.tup, values[2], 'v');
	tuple_normalize(&c->norm, &tmp.tup);
	c->d = ft_atod(values[3]);
	c->closed = ft_atoi(values[5]);
	set_tuple(&tmp.tup, values[6], 'c');
	tuple_scalar_multiply(&c->color, &tmp.tup, COLOR_CF);
	mat_with_col(&s->shapes[s->shape_count]->matrl, &c->color);
	handle_cone_helper(&tmp, c);
	matrix_multiply(&s->shapes[s->shape_count]->trans, &tmp.trans, &tmp.m);
	s->shape_count++;
	return (true);
}

static void	handle_cube_helper(t_tmp *tmp, t_cube *c)
{
	if (tuple_equals(&c->norm, &tmp->norm))
	{
		matrix_identity(&c->trans, 4);
	}
	else
	{
		tuple_vector(&tmp->tup, 0, 1, 0);
		rotate_align(&c->trans, &tmp->tup, &c->norm);
	}
	matrix_translate(&tmp->m, &c->center);
	matrix_multiply(&tmp->trans, &tmp->m, &c->trans);
	tuple_point(&tmp->tup, c->side / 2, c->side / 2, c->side / 2);
	matrix_scale(&tmp->m, &tmp->tup);
}

bool	handle_cube(char **values, t_scene *s)
{
	t_tmp	tmp;
	t_cube	*c;

	s->shapes[s->shape_count] = make_shape('u', cube_cube());
	c = (t_cube *)s->shapes[s->shape_count]->shape;
	set_tuple(&c->center, values[1], 'p');
	set_tuple(&tmp.tup, values[2], 'v');
	tuple_normalize(&c->norm, &tmp.tup);
	c->side = ft_atod(values[3]);
	set_tuple(&tmp.tup, values[4], 'c');
	tuple_scalar_multiply(&c->color, &tmp.tup, COLOR_CF);
	mat_with_col(&s->shapes[s->shape_count]->matrl, &c->color);
	tuple_vector(&tmp.tup, 1, 1, 0);
	tuple_normalize(&tmp.norm, &tmp.tup);
	handle_cube_helper(&tmp, c);
	matrix_multiply(&s->shapes[s->shape_count]->trans, &tmp.m, &tmp.trans);
	s->shape_count++;
	return (true);
}
