/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 13:42:31 by sbocanci         ###   ########.fr       */
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
		tuple_copy(&comps->shape->matrl.color, &comps->yellow);
	}
	else
	{
		tuple_copy(&comps->shape->matrl.color, &comps->blue);
	}
}

/*
** This puts a checkboard pattern on the plane object
** The size of the pattern can be set in .rt configuratino file
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
