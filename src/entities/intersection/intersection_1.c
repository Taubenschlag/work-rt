/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/02 16:16:56 by sbocanci         ###   ########.fr       */
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
	if (nl != NULL)
	{
		while (++i < (*list)->size)
			nl->list[i] = (*list)->list[i];
		nl->list[i] = new_elem;
	}
	if ((*list)->list)
		free((*list)->list);
	if (*list)
		free(*list);
	*list = nl;
}

t_intersection_list	*intersect_world(t_ray *r, t_world *w, t_tmp_m *m_tmp)
{
	t_i_tmp				tmp;
	t_intersection_list	*unsorted[2048];

	tmp.i = w->shape_counter;
	tmp.size = 0;
	while (--tmp.i >= 0)
	{
		unsorted[tmp.i] = intersect_shape(w->shapes[tmp.i], r, m_tmp);
		if (unsorted[tmp.i] == NULL)
			return (free_unsorted_list(w->shape_counter, unsorted), NULL);
		tmp.size += unsorted[tmp.i]->size;
	}
	w->merged = intersection_list_make(tmp.size);
	if (w->merged == NULL)
		return (free_unsorted_list(w->shape_counter, unsorted), NULL);
	tmp.size = -1;
	tmp.i = -1;
	while (++tmp.i < w->shape_counter)
	{
		tmp.j = -1;
		while (++tmp.j < unsorted[tmp.i]->size)
			w->merged->list[++tmp.size] = unsorted[tmp.i]->list[tmp.j];
	}
	free_unsorted_list(w->shape_counter, unsorted);
	return (w->merged);
}

void	precomp(t_computations	*comps, t_intersection *i, \
					t_ray *r, t_tmp_m *m_tmp)
{
	t_tuple	tmp;

	comps->t = i->t;
	comps->shape = i->shape;
	ray_position(&comps->point, r, i->t);
	tuple_negate(&comps->eyev, &r->dir);
	shape_normal_at(&comps->normv, i->shape, &comps->point, m_tmp);
	if (tuple_dot_product(&comps->normv, &comps->eyev) < 0)
	{
		comps->inside = 1;
		tuple_negate(&comps->normv, &comps->normv);
	}
	else
		comps->inside = 0;
	tuple_scalar_multiply(&tmp, &comps->normv, 0.0001);
	tuple_add(&comps->overpoint, &comps->point, &tmp);
	set_checkboard_pattern_colors(comps);
}

/*
** Calculate valid intersections and shade result
** also switches the pattern colors based on shape type
*/
void	shade_hit(t_world *w, t_computations *cs, \
					t_light *current, t_tmp_m *m_tmp)
{
	if (cs->shape->type == 's' && cs->shape->matrl.pattern == 1)
		stripe_at_pattern(cs);
	else if (cs->shape->type == 'p' && cs->shape->matrl.pattern > 0)
		checkboard_pattern_plane(cs);
	make_l_p(&m_tmp->pack, current, cs);
	lightning(&m_tmp->color, &m_tmp->pack, \
				in_shadow(w, &cs->overpoint, current, m_tmp));
}

/*
** This is where the beginning of intersections start to be calculated
** t_intersection_list *l - holds temporary list of all intersections
** t_intersection *i - is filtered list of valid intersections where the
** shortest values for given intersections are stored
**
** In this function color_at() the heaviest calculations are done,
** it does main color calculation for each pixel of the canvas, and
** it is returned/stored in 'm_tmp->color' tupple variable which used directly
** in 'render()' function to set pixel color in canvas to save image as .bmp
** or in 'argb_render()' to convert color to RGBA for display with mlx library.
** the logic inside is the followng: 
**
** 'intersect_world()' handles ray intersection with the scene 
** to find all intersection points at one given pixel 
** (the memory usage here can be optimized in the function 
** to render images faster using stack and fixed-reasonable intersects size).
** 
** 'hit()' finction calculates the closest intersection, and 
** if it finds it 'shade_hit()' is used to calc the shading for that point.
**
** 'shade_hit()' uses the 'make_l_p()' and 'lightning()' functions to calculate
** the color based on the material, lights, and shadows.
** So, after shading with the ambient light, it loops through each point light,
** the color is accumulated for each light into the m_tmp->color tuple
*/
void	color_at(t_world *w, t_ray *r, t_tmp_m *m_tmp)
{
	t_intersection_list	*l;
	t_intersection		*i;
	t_computations		c;
	int					j;

	j = -1;
	l = intersect_world(r, w, m_tmp);
	i = hit(l);
	if (!i)
		tuple_color(&m_tmp->color, 0, 0, 0);
	else
	{
		precomp(&c, i, r, m_tmp);
		shade_hit(w, &c, &w->amb, m_tmp);
		while (++j < w->lights_counter)
		{
			precomp(&c, i, r, m_tmp);
			tuple_copy(&m_tmp->tmp_clr_1, &m_tmp->color);
			shade_hit(w, &c, w->lights[j], m_tmp);
			tuple_copy(&m_tmp->tmp_clr_2, &m_tmp->color);
			tuple_add(&m_tmp->color, &m_tmp->tmp_clr_1, &m_tmp->tmp_clr_2);
		}
	}
	free(i);
}
