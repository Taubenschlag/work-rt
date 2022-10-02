/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 03:34:07 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

s_intersection	*intersect_make_shape(s_shape *s, double t)
{
	s_intersection	*i;

	i = (s_intersection *)malloc(sizeof(s_intersection));
	i->shape = s;
	i->t = t;
	return (i);
}

s_intersection_list	*intersection_list_make(int elem)
{
	s_intersection_list	*l;
	int					i;

	i = -1;
	l = (s_intersection_list *)malloc(sizeof(s_intersection_list));
	l->list = NULL;
	if (elem > 0)
		l->list = (s_intersection **)malloc(sizeof(s_intersection *) * elem);
	while (++i < elem)
		l->list[i] = NULL;
	l->size = elem;
	return (l);
}

s_intersection_list	*intersect_shape(s_shape *s, s_ray *r)
{
	s_ray				*ray;
	s_intersection_list	*list;

	list = NULL;
	ray = ray_transform(r, matrix_invert(s->trans));
	if (s->type == 's')
		list = intersection_ray_nsphere(s, ray);
	if (s->type == 'p')
		list = intersection_ray_plane(s, ray);
	if (s->type == 'u')
		list = intersection_ray_cube(s, ray);
	if (s->type == 'y')
		list = intersection_ray_cylinder(s, ray);
	if (s->type == 'o')
		list = intersection_ray_cone(s, ray);
	if (s->type == 'i')
		list = intersection_ray_triangle(s, ray);
	if (s->type == 'q')
		list = intersection_ray_square(s, ray);
	ray_free(ray);
	return (list);
}

void	intersection_list_free(s_intersection_list *l)
{
	int	i;

	i = -1;
	while (++i < l->size)
		free(l->list[i]);
	free(l->list);
}

// todo too big func
s_intersection	*hit(s_intersection_list *l)
{
	int				i;
	double			min;
	int				index;
	s_intersection	*ret;

	i = -1;
	index = -1;
	min = 0xfffffffffffff;
	ret = NULL;
	if (l->size)
	{
		while (++i < l->size)
		{
			if (l->list[i]->t >= 0 && l->list[i]->t < min)
			{
				min = l->list[i]->t;
				index = i;
			}
		}
		if (index > -1)
			ret = intersect_make_shape(l->list[index]->shape,
					l->list[index]->t);
	}
	intersection_list_free(l);
	free(l);
	return (ret);
}
