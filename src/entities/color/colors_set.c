/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 16:44:18 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	set_red(unsigned int *rgb, unsigned char red)
{
	*rgb &= *rgb & 0xffff;
	*rgb |= ((unsigned int)red) << 16;
}

void	set_green(unsigned int *rgb, unsigned char green)
{
	*rgb &= *rgb & 0xff00ff;
	*rgb |= ((unsigned int)green) << 8;
}

void	set_blue(unsigned int *rgb, unsigned char blue)
{
	*rgb &= *rgb & 0xffff00;
	*rgb |= ((unsigned int)blue);
}

unsigned int	make_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned int	rgb;

	rgb = 0;
	set_red(&rgb, r);
	set_green(&rgb, g);
	set_blue(&rgb, b);
	return (rgb);
}

unsigned int	make_argb(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned int	rgb;

	rgb = 1;
	rgb &= rgb & 0xffffff;
	rgb |= ((unsigned int)r) << 24;
	rgb &= rgb & 0xff00ffff;
	rgb |= ((unsigned int)r) << 16;
	rgb &= rgb & 0xffff00ff;
	rgb |= ((unsigned int)g) << 8;
	rgb &= rgb & 0xffffff00;
	rgb |= ((unsigned int)b);
	return (rgb);
}
