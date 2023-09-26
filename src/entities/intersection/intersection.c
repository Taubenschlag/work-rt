/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/26 19:34:23 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

/*
*/
t_intersection	*intersect_make_shape(t_shape *s, double t)
{
	t_intersection	*i;

	i = (t_intersection *)malloc(sizeof(t_intersection));
	if (i == NULL)
		return (NULL);
	i->shape = s;
	i->t = t;
	return (i);
}

t_intersection_list	*intersection_list_make(int elem)
{
	t_intersection_list	*l;
	int					i;

	i = -1;
	l = (t_intersection_list *)malloc(sizeof(t_intersection_list));
	if (l == NULL)
		return (NULL);
	l->list = NULL;
	if (elem > 0)
	{
		l->list = (t_intersection **)malloc(sizeof(t_intersection *) * elem);
		if (l->list == NULL)
		{
			free(l);
			return (NULL);
		}
	}
	while (++i < elem)
		l->list[i] = NULL;
	l->size = elem;
	return (l);
}

t_intersection_list	*intersect_shape(t_shape *s, t_ray *r, t_tmp_m *m_tmp)
{
	t_ray				ray;
	t_intersection_list	*list;

	list = NULL;
	matrix_invert(m_tmp, &s->trans);
	ray_transform(&ray, r, &m_tmp->inv);
	if (s->type == 's')
		list = intersection_ray_nsphere(s, &ray);
	if (s->type == 'p')
		list = intersection_ray_plane(s, &ray);
	if (s->type == 'u')
		list = intersection_ray_cube(s, &ray);
	if (s->type == 'y')
		list = intersection_ray_cylinder(s, &ray);
	if (s->type == 'o')
		list = intersection_ray_cone(s, &ray);
	if (s->type == 'i')
		list = intersection_ray_triangle(s, &ray);
	if (s->type == 'q')
		list = intersection_ray_square(s, &ray);
	return (list);
}

/*
void	intersection_list_free(t_intersection_list **l)
{
	int	i;

	i = -1;
	while (++i < (*l)->size)
		free((*l)->list[i]);
	free((*l)->list);
	free(*l);
}
*/
t_intersection	*hit(t_intersection_list *l)
{
	int				i;
	double			min;
	int				index;
	t_intersection	*ret;

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
	intersection_list_free(&l);
	return (ret);
}
