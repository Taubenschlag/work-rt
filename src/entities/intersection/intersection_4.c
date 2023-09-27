/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/27 09:54:13 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	triangle_determinant(t_triangle *tr, t_ray *ray)
{
	tuple_cross_product(&tr->dir_cros, &ray->dir, &tr->e2);
	tr->det = tuple_dot_product(&tr->e1, &tr->dir_cros);
}

void	triangle_edge_handling(t_triangle *tr, t_ray *ray)
{
	tr->f = 1.0 / tr->det;
	tuple_substract(&tr->a_to_org, &ray->origin, &tr->a);
	tr->u = tr->f * tuple_dot_product(&tr->a_to_org, &tr->dir_cros);
}

void	triangle_actual_strike(t_triangle *tr, t_ray *ray)
{
	tuple_cross_product(&tr->or_crs, &tr->a_to_org, &tr->e1);
	tr->v = tr->f * tuple_dot_product(&ray->dir, &tr->or_crs);
}

t_intersection_list	*intersection_ray_triangle(t_shape *s, t_ray *ray)
{
	t_triangle			*tr;
	t_intersection_list	*ret;

	tr = (t_triangle *)s->shape;
	ret = intersection_list_make(0);
	if (ret == NULL)
		return (NULL);
	triangle_determinant(tr, ray);
	if (fabs(tr->det) < 0.0001)
		return (ret);
	triangle_edge_handling(tr, ray);
	if (tr->u < 0 - 0.0001 || tr->u > 1 + 0.00001)
		return (ret);
	triangle_actual_strike(tr, ray);
	if (tr->v < 0 - 0.0001 || (tr->v + tr->u) > 1 + 0.00001)
		return (ret);
	tr->t = tr->f * tuple_dot_product(&tr->e2, &tr->or_crs);
	add_intersection(intersect_make_shape(s, tr->t), &ret);
	return (ret);
}

t_intersection_list	*intersection_ray_square(t_shape *s, t_ray *ray)
{
	t_intersection_list	*ret;
	t_intersection_list	*temp;
	t_shape				*tr;
	t_square			*q;

	q = (t_square *)s->shape;
	tr = make_shape('i', (t_triangle *)&q->t2);
	if (tr == NULL)
		return (NULL);
	ret = intersection_ray_triangle(tr, ray);
	free(tr);
	if (ret->size == 1)
	{
		ret->list[0]->shape = s;
		return (ret);
	}
	intersection_list_free(&ret);
	tr = make_shape('i', (t_triangle *)&q->t1);
	if (tr == NULL)
		return (NULL);
	temp = intersection_ray_triangle(tr, ray);
	free(tr);
	if (temp->size == 1)
		temp->list[0]->shape = s;
	return (temp);
}
