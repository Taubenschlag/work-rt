/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/29 20:10:10 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

t_cube	*cube_cube(void)
{
	t_cube	*c;

	c = (t_cube *)malloc(sizeof(t_cube));
	if (c == NULL)
		return (NULL);
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
