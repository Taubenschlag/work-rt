/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/29 20:11:10 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

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
}

t_sphere	*nsphere_nsphere(t_tuple *centre)
{
	t_sphere	*nsphere;

	nsphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (nsphere == NULL)
		return (NULL);
	tuple_copy(&nsphere->centre, centre);
	return (nsphere);
}

t_sphere	*nsphere_unit(t_tuple *centre)
{
	return (nsphere_nsphere(centre));
}

void	nsphere_free(t_sphere *s)
{
	free(s);
}
