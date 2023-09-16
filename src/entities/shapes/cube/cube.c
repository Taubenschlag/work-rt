/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/16 21:49:52 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

t_cube	*cube_cube(void)
{
	t_cube	*c;

	c = (t_cube *)malloc(sizeof(t_cube));
	return (c);
}

void	cube_free(t_cube *c)
{
	free(c);
}


void	cube_normal_at(t_tuple *res, t_tuple *p)
{
	double	max_one;

	max_one = dmax(dmax(fabs(p->x), fabs(p->y)), fabs(p->z));
	if (max_one == fabs(p->x))
	{
		tuple_vector(res, p->x, 0, 0);
		return ;
	}
	if (max_one == fabs(p->y))
	{
		tuple_vector(res, 0, p->y, 0);
		return ;
	}
	tuple_vector(res, 0, 0, p->z);
}

/*
t_tuple	*cube_normal_at(t_tuple *p)
{
	double	max_one;

	max_one = dmax(dmax(fabs(p->x), fabs(p->y)), fabs(p->z));
	if (max_one == fabs(p->x))
		return (tuple_vector(p->x, 0, 0));
	if (max_one == fabs(p->y))
		return (tuple_vector(0, p->y, 0));
	return (tuple_vector(0, 0, p->z));
}
*/