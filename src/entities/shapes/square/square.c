/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 19:55:20 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

t_square	*square(void)
{
	t_square	*square;
	t_tuple	t_a;
	t_tuple	t_b;
	t_tuple	t_c;

	square = (t_square *)malloc(sizeof(t_square));
	tuple_point(&t_a, -1, 1, 0);	
	tuple_point(&t_b, -1, -1, 0);
	tuple_point(&t_c, 1, 1, 0);
	triangle_coordinates(&square->t1, &t_a, &t_b, &t_c); 
	tuple_point(&t_a, 1, -1, 0);	
	triangle_coordinates(&square->t2, &t_a, &t_c, &t_b); 
	return (square);
}

void	square_normale_at(t_tuple *res)
{
	tuple_vector(res, 0, 0, 1);
}

void	free_square(t_square *t)
{
	free(t);
}