/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/16 22:08:08 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

/*
t_triangle	*triangle_coordinates(t_tuple *a, t_tuple *b, t_tuple *c)
{
	t_triangle	*tr;

	tr = (t_triangle *)malloc(sizeof(t_triangle));
	tr->a = a;
	tr->b = b;
	tr->c = c;
	tr->e1 = tuple_substract(tuple_copy(b), tuple_copy(a));
	tr->e2 = tuple_substract(tuple_copy(c), tuple_copy(a));
	tr->n = tuple_normalize(tuple_cross_product(tr->e1, tr->e2));
	return (tr);
}

void	free_triangle(t_triangle *t)
{
	tuple_free(t->a);
	tuple_free(t->b);
	tuple_free(t->c);
	tuple_free(t->e1);
	tuple_free(t->e2);
	tuple_free(t->n);
	free(t);
}

t_tuple	*triangle_normale_at(t_triangle *t)
{
	return (tuple_copy(t->n));
}
*/

void	triangle_coordinates(t_triangle *tr, t_tuple *a, t_tuple *b, t_tuple *c)
{
	//t_triangle	*tr;
	t_tuple	tmp;

	//tr = (t_triangle *)malloc(sizeof(t_triangle));
	tuple_copy(&tr->a, a);
	tuple_copy(&tr->b, b);
	tuple_copy(&tr->c, c);
	tuple_substract(&tr->e1, b, a);
	tuple_substract(&tr->e2, c, a);
	tuple_cross_product(&tmp, &tr->e1, &tr->e2);
	tuple_normalize(&tr->n, &tmp);
	/*
	tr->a = a;
	tr->b = b;
	tr->c = c;
	tr->e1 = tuple_substract(tuple_copy(b), tuple_copy(a));
	tr->e2 = tuple_substract(tuple_copy(c), tuple_copy(a));
	tr->n = tuple_normalize(tuple_cross_product(tr->e1, tr->e2));
	return (tr);
	*/
}

void	triangle_normale_at(t_tuple *res, t_triangle *t)
{
	tuple_copy(res, &t->n);
}
