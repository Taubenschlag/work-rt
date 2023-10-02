/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/02 13:42:50 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	set_checkboard_pattern_colors(t_computations *comps)
{
	tuple_color(&comps->white, 1.0, 1.0, 1.0);
	tuple_color(&comps->black, 0.0, 0.0, 0.0);
	tuple_color(&comps->red, 0.6, 0.0, 0.0);
	tuple_color(&comps->green, 0.0, 1.0, 0.0);
	tuple_color(&comps->blue, 0.0, 0.0, 0.7);
	tuple_color(&comps->yellow, 1.0, 0.7, 0.0);
	tuple_color(&comps->gray, 0.3, 0.3, 0.3);
}

/*
** Function bellow performs calculations for mapping a sphere 
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
*/
void	sphere_pattern(t_computations *comps)
{
	double	tmp;
	double	u;
	double	v;
	double	u_frac;
	double	v_frac;

	u = atan2(comps->point.y, comps->point.x);
	tmp = sqrt(comps->point.x * comps->point.x \
				+ comps->point.y * comps->point.y);
	v = atan2(comps->point.z, tmp);
	u = u / (2 * M_PI);
	v = v / M_PI;
	u_frac = fmod(u, 1.0);
	v_frac = fmod(v, 1.0);
	tmp = fmod(u_frac + v_frac, 2.0);
	if (tmp < 0.30)
	{
		tuple_copy(&comps->shape->matrl.color, &comps->yellow);
	}
	else
	{
		tuple_copy(&comps->shape->matrl.color, &comps->blue);
	}
}

/*
** floor() returns the largest integer less than or equal to a given number
** eg: 
** floor(1.1) = 1, since 1 is the largest integer less than or equal to 1.1
** floor(0.3) = 0, since 0 is the largest integer less than or equal to 0.3
** floor(-0.2) = -1, since -1 is the largest integer less than or equal to -0.2
** 
** This function puts a striped pattern on the plane object
*/
void	stripe_at_pattern(t_computations *comps)
{
	double	x;
	double	cnst;

	cnst = 10.0;
	x = comps->point.x;
	if ((int)(floor(x / cnst)) % 2 == 0)
	{
		tuple_copy(&comps->shape->matrl.color, &comps->white);
	}
	else
	{
		tuple_copy(&comps->shape->matrl.color, &comps->black);
	}
}

/*
** This puts a checkboard pattern on the plane object
*/
void	checkboard_pattern_plane(t_computations *comps)
{
	double	x;
	double	z;
	int		x_block;
	int		z_block;
	int		is_odd;

	x = comps->point.x;
	z = comps->point.z;
	x_block = (int)floor(x / comps->shape->matrl.pattern);
	z_block = (int)floor(z / comps->shape->matrl.pattern);
	is_odd = (x_block % 2 + z_block) % 2;
	if (is_odd)
	{
		tuple_copy(&comps->shape->matrl.color, &comps->white);
	}
	else
	{
		tuple_copy(&comps->shape->matrl.color, &comps->black);
	}
}
