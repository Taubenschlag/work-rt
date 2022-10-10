/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 02:37:41 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_shape	*test_shape(void)
{
	t_shape	*sh;

	sh = make_shape('s', NULL);
	sh->matrl = material_make_default();
	return (sh);
}

t_shape	*make_shape(char type, void *shape_itself)
{
	t_shape	*sh;

	sh = (t_shape *)malloc(sizeof(t_shape));
	sh->shape = shape_itself;
	sh->type = type;
	sh->trans = matrix_identity(4);
	sh->matrl = NULL;
	return (sh);
}

void	*set_transform(t_shape *sh, t_matrix *trans)
{
	matrix_free(sh->trans);
	sh->trans = trans;
	return (sh);
}

//TODO toolong
//todo mem
t_tuple	*shape_normal_at(t_shape *s, t_tuple *p)
{
	t_tuple	*loc_pnt;
	t_tuple	*loc_normal;
	t_tuple	*wrld_normal;

	loc_pnt = tuple_apply_trans_matrix(matrix_invert(s->trans), tuple_copy(p));
	if (s->type == 's' )
		return (nsphere_normal_at(loc_pnt, s->trans));
	else if (s->type == 'p')
		loc_normal = plane_normal_at();
	else if (s->type == 'u')
		loc_normal = cube_normal_at(loc_pnt);
	else if (s->type == 'y')
		loc_normal = cylinder_normale_at(loc_pnt, (t_cylinder *)s->shape);
	else if (s->type == 'o')
		loc_normal = cone_normale_at(loc_pnt, (t_cone *)s->shape);
	else if (s->type == 'i')
		loc_normal = triangle_normale_at((t_triangle *) s->shape);
	else if (s->type == 'q')
		loc_normal = square_normale_at();
	else
		return (NULL);
	wrld_normal = tuple_apply_trans_matrix(
			matrix_transpose(matrix_copy(s->trans)), loc_normal);
	tuple_free(loc_pnt);
	wrld_normal->type = 0;
	return (tuple_normalize(wrld_normal));
}

void	free_shape(t_shape *s)
{
	if (s->type == 's' )
		nsphere_free((t_sphere *)s->shape);
	else if (s->type == 'p')
		plane_free((plane *)s->shape);
	else if (s->type == 'u')
		cube_free((t_cube *)s->shape);
	else if (s->type == 'y')
		cylinder_free((t_cylinder *)s->shape);
	else if (s->type == 'o')
		free(s->shape);
	else if (s->type == 'i')
		free_triangle((t_triangle *) s->shape);
	else if (s->type == 'q')
		free_square((t_square *) s->shape);
	material_free(s->matrl);
	matrix_free(s->trans);
	free(s);
}
