/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 03:02:57 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

t_square	*square(void)
{
	t_square	*ret;

	ret = (t_square *)malloc(sizeof(t_square));
	ret->t1 = triangle_coordinates(
			tuple_point(-1, 1, 0),
			tuple_point(-1, -1, 0),
			tuple_point(1, 1, 0));
	ret->t2 = triangle_coordinates(
			tuple_point(1, -1, 0),
			tuple_point(1, 1, 0),
			tuple_point(-1, -1, 0));
	return (ret);
}

t_tuple	*square_normale_at(void)
{
	return (tuple_vector(0, 0, 1));
}

void	free_square(t_square *t)
{
	free_triangle(t->t1);
	free_triangle(t->t2);
	free(t);
}
