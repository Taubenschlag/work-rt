/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 02:28:37 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

s_tuple	*tuple_vector(double x, double y, double z)
{
	s_tuple	*t;

	t = (s_tuple *)malloc(sizeof(s_tuple));
	t->x = x;
	t->y = y;
	t->z = z;
	t->type = IS_VECTOR;
	return (t);
}

s_tuple	*tuple_point(double x, double y, double z)
{
	s_tuple	*t;

	t = (s_tuple *)malloc(sizeof(s_tuple));
	t->x = x;
	t->y = y;
	t->z = z;
	t->type = IS_POINT;
	return (t);
}

void	tuple_free(s_tuple *tuple)
{
	free(tuple);
}

int	tuple_is_vector(s_tuple *tuple)
{
	return (tuple->type == IS_VECTOR);
}
