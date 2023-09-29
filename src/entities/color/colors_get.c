/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/29 19:30:18 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

unsigned char	get_red(unsigned int rgb)
{
	rgb <<= 8;
	return ((unsigned char)(rgb >> 24));
}

unsigned char	get_green(unsigned int rgb)
{
	rgb <<= 16;
	return ((unsigned char)(rgb >> 24));
}

unsigned char	get_blue(unsigned int rgb)
{
	rgb <<= 24;
	return ((unsigned char)(rgb >> 24));
}

unsigned int	tuple_to_rgb(t_tuple *rgb_tuple)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)(rgb_tuple->x * 255);
	g = (unsigned int)(rgb_tuple->y * 255);
	b = (unsigned int)(rgb_tuple->z * 255);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (make_rgb(
			(unsigned char)r,
			(unsigned char)g,
			(unsigned char)b));
}

unsigned int	tuple_to_argb(t_tuple *rgb_tuple)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)(rgb_tuple->x * 127);
	g = (unsigned int)(rgb_tuple->y * 127);
	b = (unsigned int)(rgb_tuple->z * 127);
	if (r > 127)
		r = 127;
	if (g > 127)
			g = 127;
	if (b > 127)
		b = 127;
	return (make_argb(
			(unsigned char)r,
			(unsigned char)g,
			(unsigned char)b));
}
