/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/16 19:19:16by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

/*
** ..0.3 here is an experimental value to map coordinates to checkboard squares
*/
void	get_checkboard_coords(t_computations *comps)
{
	comps->is_odd = false;
	tuple_color(&comps->even_color, 1.0, 1.0, 1.0);
	tuple_color(&comps->odd_color, 0.0, 0.0, 0.0);
}

/*
** This function performs calculations for mapping a sphere 
** to a checkerboard pattern.
** UV coordinates are used to map a 2D texture onto a 3D model. 
** The u and v values range from 0 to 1 and correspond to the 
** horizontal and vertical axes of the texture image.
**
** The u coordinate maps to the horizontal axis of the texture image.
** u=0 is the left edge, u=1 is the right edge.
** The v coordinate maps to the vertical axis. 
** v=0 is the bottom edge, v=1 is the top edge.
**
** The u coordinate should be calculated as the 
** azimuthal angle from -π to π. This can be done by taking the 
** atan2 of the y and x coordinates.
** The v coordinate should be the inclination angle from 0 to π. 
** This can be calculated as acos(z / radius)
**
** To check if a square is odd or even, we take the fractional part 
** of u and v by calling fmod. 
** The fractions should be in the range [0,1]
**
** u_frac and v_frac values should vary as expected over the sphere
** If both fracs are < 0.5, it's an even square. Otherwise it's odd.
** (u and v calculations should map the full 0 to 2π and 0 to π range 
** over the sphere surface.)
** The goal is to have u and v (and their fractions) cycle 
** through their full 0-1 range as the point varies over the entire
** sphere surface.

void	sphere_checkboard_parity(t_computations *comps)
{
	double	tmp;
	double	u;
	double	v;
	double	u_frac;
	double	v_frac;

	u = atan2(comps->point.y, comps->point.x) / (2 * M_PI);
	//v = acos(comps->point.z / 40) / M_PI;
	tmp = comps->point.z / 40;
	if (tmp < -1)
		tmp = -1;
	else if (tmp > 1)
		tmp = 1;
	v = acos(tmp) / M_PI;

	u_frac = fmod(u, 1.0);
	v_frac = fmod(v, 1.0);

	print_tuple(&comps->point);
	printf("u:[%.5f], v:[%.5f], u_frac:[%.5f], v_frac:[%.5f]\n", u, v, u_frac, v_frac);
	if (u_frac < 0.5 && v_frac < 0.5)	
	{
		comps->is_odd = false;
		tuple_copy(&comps->shape->matrl.color, &comps->even_color);
	}
	else
	{
		comps->is_odd = true;
		tuple_copy(&comps->shape->matrl.color, &comps->odd_color);
	}
}
void	plane_checkboard_parity(t_computations *comps)
{
	t_tuple	u_axis;
	double	u;
	double	v;
	double	u_frac;
	double	v_frac;
	
	tuple_cross_product(&u_axis, &comps->normv, &comps->point);
	u = tuple_dot_product(&comps->point, &u_axis);
	v = tuple_dot_product(&comps->point, &comps->normv);
	u_frac = fmod(u, 1.0);
	v_frac = fmod(v, 1.0);
	if (u_frac < 0.5 && v_frac < 0.5)	
	{
		comps->is_odd = false;
		tuple_copy(&comps->shape->matrl.color, &comps->even_color);
	}
	else
	{
		comps->is_odd = true;
		tuple_copy(&comps->shape->matrl.color, &comps->odd_color);
	}
}
void	stripe_at_pattern(t_computations *comps)
{
	double	x;
	double	y;
	double	z;
	double	mod;
	double cnst = 10.0;

	x = comps->point.x;
	y = comps->point.y;
	z = comps->point.z;
	mod = fmod(x, cnst);

	if ((x > 0 && mod > (cnst / 2)) || (x < 0 && fabs(mod) <= (cnst / 2)))
	{
		tuple_copy(&comps->shape->matrl.color, &comps->even_color);
	}
	else if ((x > 0 && mod < (cnst / 2) ) || (x < 0 && fabs(mod) >= (cnst / 2)))
	{
		tuple_copy(&comps->shape->matrl.color, &comps->odd_color);
	}
}


void	stripe_at_pattern(t_computations *comps)
{
	double	x;
	double	cnst = 10.0;

	x = comps->point.x;

	if ((int)(floor(x / cnst)) % 2 == 0)
	{
		tuple_copy(&comps->shape->matrl.color, &comps->even_color);
	}
	else
	{
		tuple_copy(&comps->shape->matrl.color, &comps->odd_color);
	}
}
*/

typedef struct s_ptrn
{
	double 	cnst;
	double	x;
	double	y;
	double	z;
	double	mod_x;
	double	mod_y;
	double	mod_z;
	double	mod;
}	t_ptrn;

void	checker_at_pattern(t_computations *comps)
{
	t_ptrn	pt;
	
	pt.cnst = 10.0;
	pt.x = comps->point.x;
	pt.y = comps->point.y;
	pt.z = comps->point.z;
	pt.mod_x = fmod(pt.x, pt.cnst);
	pt.mod_y = fmod(pt.y, pt.cnst);
	pt.mod_z = fmod(pt.z, pt.cnst);

	pt.mod = fmod(fabs(pt.x) + fabs(pt.y) + fabs(pt.z), pt.cnst);
	printf("mod:[%.4f]\n", pt.mod);
	if (pt.mod < pt.cnst / 2)
	{
		tuple_copy(&comps->shape->matrl.color, &comps->even_color);
	}
	else
	{
		tuple_copy(&comps->shape->matrl.color, &comps->odd_color);
	}
/*
	if ((int)(floor(pt.mod_x / pt.cnst)) % 2 == 0)
		tuple_copy(&comps->shape->matrl.color, &comps->even_color);
	else
		tuple_copy(&comps->shape->matrl.color, &comps->odd_color);
	if ((int)(floor(pt.mod_y / pt.cnst)) % 2 == 0)
		tuple_copy(&comps->shape->matrl.color, &comps->even_color);
	else
		tuple_copy(&comps->shape->matrl.color, &comps->odd_color);
	if ((int)(floor(pt.mod_z / ptrn.cnst)) % 2 == 0)
		tuple_copy(&comps->shape->matrl.color, &comps->even_color);
	else
		tuple_copy(&comps->shape->matrl.color, &comps->odd_color);
*/
}

void	sphere_checkboard_parity(t_computations *comps)
{
	double	tmp;
	double	u;
	double	v;
	double	u_frac;
	double	v_frac;

	u = atan2(comps->point.y, comps->point.x);
	tmp = sqrt(comps->point.x * comps->point.x + comps->point.y * comps->point.y);
	v = atan2(comps->point.z, tmp);

	u = u / (2 * M_PI);
	v = v / M_PI;

	u_frac = fmod(u, 1.0);
	v_frac = fmod(v, 1.0);
	tmp = fmod(u_frac + v_frac, 2.0);

	//printf("u:[%.5f], v:[%.5f], u_frac:[%.5f], v_frac:[%.5f]", u, v, u_frac, v_frac);
	//printf("\ttmp:[%.5f]\n", tmp);
	if (tmp < 0.30)	
	{
		//printf("even square\n");
		comps->is_odd = false;
		tuple_copy(&comps->shape->matrl.color, &comps->even_color);
	}
	else
	{
		//printf("odd square\n");
		comps->is_odd = true;
		tuple_copy(&comps->shape->matrl.color, &comps->odd_color);
	}
}
/* ****** */

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
	t_i_tmp	tmp;
	t_intersection_list	*unsorted[w->shape_counter];

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

void	precomp(t_computations	*comps, t_intersection *i, t_ray *r, t_tmp_m *m_tmp)
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
	/* DEBUG */
	get_checkboard_coords(comps);
}

void	shade_hit(t_world *w, t_computations *cs, t_light *current, t_tmp_m *m_tmp)
{
	if (cs->shape->type == 's')
		sphere_checkboard_parity(cs);
	else if (cs->shape->type == 'p')
		checker_at_pattern(cs);
		//stripe_at_pattern(cs);
	make_l_p(&m_tmp->pack, current, cs);
	lightning(&m_tmp->color, &m_tmp->pack,
			in_shadow(w, &cs->overpoint, current, m_tmp));
}

/*
void	shade_hit(t_world *w, t_computations *cs, t_light *current, t_tmp_m *m_tmp)
{
	make_l_p(&m_tmp->pack, current, cs);
	lightning(&m_tmp->color, &m_tmp->pack,
			in_shadow(w, &cs->overpoint, current, m_tmp));
}
*/
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
