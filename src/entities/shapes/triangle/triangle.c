/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 19:56:25 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

void	free_triangle(t_triangle *t)
{
	free(t);
}

void	triangle_coordinates(t_triangle *tr, t_tuple *a, t_tuple *b, t_tuple *c)
{
	t_tuple	tmp;

	tuple_copy(&tr->a, a);
	tuple_copy(&tr->b, b);
	tuple_copy(&tr->c, c);
	tuple_substract(&tr->e1, b, a);
	tuple_substract(&tr->e2, c, a);
	tuple_cross_product(&tmp, &tr->e1, &tr->e2);
	tuple_normalize(&tr->n, &tmp);
}

void	triangle_normale_at(t_tuple *res, t_triangle *t)
{
	tuple_copy(res, &t->n);
}
