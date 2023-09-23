/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/23 13:37:40 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

void	free_triangle(t_triangle *t)
{
	free(t);
}

void	triangle_coordinates(t_triangle *tr)
{
	t_tuple	tmp;

	tuple_substract(&tr->e1, &tr->b, &tr->a);
	tuple_substract(&tr->e2, &tr->c, &tr->a);
	tuple_cross_product(&tmp, &tr->e1, &tr->e2);
	tuple_normalize(&tr->n, &tmp);
}

void	triangle_normale_at(t_tuple *res, t_triangle *t)
{
	tuple_copy(res, &t->n);
}
