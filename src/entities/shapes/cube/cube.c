/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 21:49:47 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

s_cube	*cube_cube(void)
{
	s_cube	*c;

	c = (s_cube *)malloc(sizeof(s_cube));
	return (c);
}

void	cube_free(s_cube *c)
{
	free(c);
}

s_tuple	*cube_normal_at(s_tuple *p)
{
	double	max_one;

	max_one = max_d(max_d(fabs(p->x), fabs(p->y)), fabs(p->z));
	if (max_one == fabs(p->x))
		return (tuple_vector(p->x, 0, 0));
	if (max_one == fabs(p->y))
		return (tuple_vector(0, p->y, 0));
	return (tuple_vector(0, 0, p->z));
}
