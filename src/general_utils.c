/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/09/30 21:33:09 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads_global/minirt.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	dmin(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	dmax(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	mins(double *a, int length)
{
	int		i;
	double	min;

	min = INFINITY * 1;
	i = -1;
	while (++i < length)
	{
		if (a[i] < min)
			min = a[i];
	}
	return (min);
}

double	maxs(double *a, int length)
{
	int		i;
	double	max;

	max = INFINITY * -1;
	i = -1;
	while (++i < length)
	{
		if (a[i] > max)
			max = a[i];
	}
	return (max);
}
