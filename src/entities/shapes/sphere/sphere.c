/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 03:05:32 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

t_tuple	*nsphere_normal_at(t_tuple *p, t_matrix *m)
{
	t_tuple	*obj_normal;
	t_tuple	*world_normal;

	obj_normal = tuple_substract(tuple_copy(p), tuple_point(0, 0, 0));
	world_normal = tuple_apply_trans_matrix(
			matrix_transpose(matrix_invert(m)), obj_normal);
	world_normal->type = IS_VECTOR;
	tuple_free(p);
	return (tuple_normalize(world_normal));
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
