/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/16 20:20:23 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

/*
t_tuple	*nsphere_normal_at(t_tuple *p, t_matrix *m, t_tmp_m *m_tmp)
{
	t_tuple	*obj_normal;
	t_tuple	*world_normal;

	matrix_invert(m_tmp, m);
	matrix_transpose(&m_tmp->transposed, &m_tmp->inv);
	obj_normal = tuple_substract(tuple_copy(p), tuple_point(0, 0, 0));
	world_normal = tuple_apply_trans_matrix(&m_tmp->transposed, obj_normal);
	world_normal->type = IS_VECTOR;
	tuple_free(p);
	return (tuple_normalize(world_normal));
}
*/
void	nsphere_normal_at(t_tuple *res, t_tuple *p, t_matrix *m, t_tmp_m *m_tmp)
{
	t_tuple	obj_normal;
	t_tuple	world_normal;
	t_tuple	tmp;

	matrix_invert(m_tmp, m);
	matrix_transpose(&m_tmp->transposed, &m_tmp->inv);
	tuple_point(&tmp, 0, 0, 0);
	tuple_substract(&obj_normal, p, &tmp);
	tuple_apply_trans_matrix(&world_normal, &m_tmp->transposed, &obj_normal);
	world_normal.type = IS_VECTOR;
	tuple_normalize(res, &world_normal);

	//obj_normal = tuple_substract(tuple_copy(p), tuple_point(0, 0, 0));
	//world_normal = tuple_apply_trans_matrix(&m_tmp->transposed, obj_normal);
	//world_normal->type = IS_VECTOR;
	//tuple_free(p);
	//return (tuple_normalize(world_normal));
}

t_sphere	*nsphere_nsphere(t_tuple *centre)
{
	t_sphere	*nsphere;

	nsphere = (t_sphere *)malloc(sizeof(t_sphere));
	nsphere->centre = centre;
	return (nsphere);
}

t_sphere	*nsphere_unit(t_tuple *centre)
{
	return (nsphere_nsphere(centre));
}

void	nsphere_free(t_sphere *s)
{
	if (s->centre)
		tuple_free((s->centre));
	free(s);
}
