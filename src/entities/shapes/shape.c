/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/11 13:50:29by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_shape	*make_shape(char type, void *shape_itself)
{
	t_shape	*sh;

	sh = (t_shape *)malloc(sizeof(t_shape));
	sh->shape = shape_itself;
	sh->type = type;
	//sh->trans = matrix_identity(4);
	matrix_identity(&sh->trans, 4);
	sh->matrl = NULL;
	return (sh);
}

/*
void	*set_transform(t_shape *sh, t_matrix *trans)
{
	matrix_free(sh->trans);
	sh->trans = trans;
	return (sh);
}
*/

//t_tuple	*world_normal_apply(t_shape *s, t_tuple *loc_pnt, t_tuple *loc_normal)
void	world_normal_apply(t_tuple *res, t_shape *s, t_tuple *loc_pnt, t_tuple *loc_normal)
{
	//t_tuple	*wrld_normal;
	/* */
	t_matrix	tmp_m;	

	//matrix_copy(tmp_m, s->trans);
	matrix_transpose(&tmp_m, &s->trans);
	tuple_apply_trans_matrix(&res, &tmp_m, loc_normal);
	res->type = 0;
	//wrld_normal = tuple_apply_trans_matrix(matrix_transpose(matrix_copy(s->trans)), loc_normal);
	//tuple_free(loc_pnt);
	//return (wrld_normal);
}

void	shape_normal_at(t_tuple *res, t_shape *s, t_tuple *p, t_tmp_m *m_tmp)
{
	t_tuple	loc_pnt;
	t_tuple	loc_normal;
	t_tuple	tmp;
	/**/
	//t_matrix inverted;
	//t_tmp_m	m_tmp;

	matrix_invert(m_tmp, &s->trans);
	/**/
	tuple_apply_trans_matrix(&loc_pnt, &m_tmp->inv, p);
	//loc_pnt = tuple_apply_trans_matrix(&m_tmp->inv, tuple_copy(p));
	//loc_pnt = tuple_apply_trans_matrix(matrix_invert(s->trans), tuple_copy(p));
	if (s->type == 's' )
	{
		nsphere_normal_at(res, &loc_pnt, &s->trans, m_tmp);
		return ;
		//return (nsphere_normal_at(loc_pnt, &s->trans, m_tmp));
		//return (nsphere_normal_at(loc_pnt, s->trans));
	}
	else if (s->type == 'p')
		plane_normal_at(&loc_normal);
	else if (s->type == 'u')
		cube_normal_at(&loc_normal, &loc_pnt);
	else if (s->type == 'y')
		cylinder_normale_at(&loc_normal, &loc_pnt, (t_cylinder *)s->shape);
	else if (s->type == 'o')
		cone_normale_at(&loc_normal, &loc_pnt, (t_cone *)s->shape);
	else if (s->type == 'i')
		triangle_normale_at(&loc_normal, (t_triangle *)s->shape);
	else if (s->type == 'q')
		square_normale_at(&loc_normal);
	else
		return ;
	world_normal_apply(&tmp, s, &loc_pnt, &loc_normal);
	tuple_normalize(res, &tmp);
	//return (tuple_normalize(world_normal_apply(s, loc_pnt, loc_normal)));
}

void	free_shape(t_shape *s)
{
	if (s->type == 's' )
		nsphere_free((t_sphere *)s->shape);
	else if (s->type == 'p')
		plane_free((t_plane *)s->shape);
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
	//matrix_free(s->trans);
	free(s);
}
