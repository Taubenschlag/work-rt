/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/29 20:09:42 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

t_square	*square(void)
{
	t_square	*square;

	square = (t_square *)malloc(sizeof(t_square));
	if (square == NULL)
		return (NULL);
	tuple_point(&square->t1.a, -1, 1, 0);
	tuple_point(&square->t1.b, -1, -1, 0);
	tuple_point(&square->t1.c, 1, 1, 0);
	triangle_coordinates(&square->t1);
	tuple_point(&square->t2.a, 1, -1, 0);
	tuple_point(&square->t2.b, -1, -1, 0);
	tuple_point(&square->t2.c, 1, 1, 0);
	triangle_coordinates(&square->t2);
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
