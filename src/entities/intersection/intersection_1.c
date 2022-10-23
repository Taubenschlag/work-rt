/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/22 23:06:51 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	add_intersection(t_intersection *new_elem,
						t_intersection_list **list)
{
	t_intersection_list	*nl;
	int					i;

	i = -1;
	nl = intersection_list_make((*list)->size + 1);
	while (++i < (*list)->size)
		nl->list[i] = (*list)->list[i];
	nl->list[i] = new_elem;
	if ((*list)->list)
		free((*list)->list);
	free(*list);
	*list = nl;
}

t_intersection_list	*intersect_world(t_ray *r, t_world *w)
{
	int					i;
	int					j;
	int					size;

	w->unsorted = malloc(sizeof(t_intersection_list *) * w->shape_counter);
	i = w->shape_counter;
	size = 0;
	while (--i >= 0)
	{
		w->unsorted[i] = intersect_shape(w->shapes[i], r);
		size += w->unsorted[i]->size;
	}
	w->merged = intersection_list_make(size);
	size = -1;
	i = -1;
	while (++i < w->shape_counter)
	{
		j = -1;
		while (++j < w->unsorted[i]->size)
			w->merged->list[++size] = w->unsorted[i]->list[j];
		free(w->unsorted[i]->list);
		free(w->unsorted[i]);
	}
	free(w->unsorted);
	return (w->merged);
}

t_computations	*precomp(t_intersection *i, t_ray *r)
{
	t_computations	*comps;
	t_tuple			*tmp;

	comps = (t_computations *)malloc(sizeof(t_computations));
	comps->t = i->t;
	comps->shape = i->shape;
	comps->point = ray_position(r, i->t);
	comps->eyev = tuple_negate(tuple_copy(r->dir));
	comps->normv = shape_normal_at(i->shape, comps->point);
	if (tuple_dot_product(comps->normv, comps->eyev) < 0)
	{
		comps->inside = 1;
		tmp = tuple_negate(tuple_copy(comps->normv));
		tuple_free(comps->normv);
		comps->normv = tmp;
	}
	else
		comps->inside = 0;
	comps->overpoint = tuple_add(tuple_copy(comps->point),
			tuple_scalar_multiply(tuple_copy(comps->normv), 0.0001));
	return (comps);
}

t_tuple	*shade_hit(t_world *w, t_computations *cs, t_light *current)
{
	return (lightning(
			make_l_p(current, cs),
			in_shadow(w, cs->overpoint, current)));
}

t_tuple	*color_at(t_world *w, t_ray *r)
{
	t_intersection_list	*l;
	t_intersection		*i;
	t_computations		*c;
	t_tuple				*color;
	int					j;

	j = -1;
	l = intersect_world(r, w);
	i = hit(l);
	if (!i)
		color = tuple_color(0, 0, 0);
	else
	{
		c = precomp(i, r);
		color = shade_hit(w, c, w->ambienace);
		free(c);
		while (++j < w->lights_counter)
		{
			c = precomp(i, r);
			color = tuple_add(color, shade_hit(w, c, w->lights[j]));
			free(c);
		}
	}
	free(i);
	return (color);
}
