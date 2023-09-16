/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/16 22:17:59 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

/*
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
*/
void	square(t_square *res)
{
	t_tuple	t_a;
	t_tuple	t_b;
	t_tuple	t_c;

	tuple_point(&t_a, -1, 1, 0);	
	tuple_point(&t_b, -1, -1, 0);
	tuple_point(&t_c, 1, 1, 0);
	triangle_coordinates(&res->t1, &t_a, &t_b, &t_c); 
	tuple_point(&t_a, 1, -1, 0);	
	triangle_coordinates(&res->t2, &t_a, &t_c, &t_b); 
}

void	square_normale_at(t_tuple *res)
{
	tuple_vector(res, 0, 0, 1);
}
