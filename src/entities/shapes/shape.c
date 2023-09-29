/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/29 20:05:05 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_shape	*make_shape(char type, void *shape_itself)
{
	t_shape	*sh;

	sh = (t_shape *)malloc(sizeof(t_shape));
	if (sh == NULL)
		return (NULL);
	sh->shape = shape_itself;
	sh->type = type;
	matrix_identity(&sh->trans, 4);
	return (sh);
}

void	world_normal_apply(t_tuple *res, t_shape *s, t_tuple *loc_normal)
{
	t_matrix	tmp_m;	

	matrix_transpose(&tmp_m, &s->trans);
	tuple_apply_trans_matrix(res, &tmp_m, loc_normal);
	res->type = 0;
}

void	shape_normal_at(t_tuple *res, t_shape *s, t_tuple *p, t_tmp_m *m_tmp)
{
	t_tuple	loc_pnt;
	t_tuple	loc_normal;
	t_tuple	tmp;

	matrix_invert(m_tmp, &s->trans);
	tuple_apply_trans_matrix(&loc_pnt, &m_tmp->inv, p);
	if (s->type == 's' )
		return (nsphere_normal_at(res, &loc_pnt, &s->trans, m_tmp));
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
	world_normal_apply(&tmp, s, &loc_normal);
	tuple_normalize(res, &tmp);
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
	free(s);
}
