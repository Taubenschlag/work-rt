/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_shape_description_checker.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:27:33 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/13 21:32:14 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

/*
 * 1 - centre
 * 2 - diameter
 * 3 - color
 */
void	check_sphere(int **counters_ptr, int *is_correct, char **str)
{
	int		*counters;
	int		i;
	double	s1;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 4)
		*is_correct = FALSE;
	else
	{
		s1 = ft_atod(str[2]);
		if (!is_tuple(str[1], FALSE)
			|| !is_tuple(str[3], TRUE)
			|| s1 <= 0.0)
			*is_correct = FALSE;
		else
			counters[SPH]++;
	}
}

/*
 * 1 - point on a t_plane
 * 2 - normale
 * 3 - color
 */
void	check_plane(int **counters_ptr, int *is_correct, char **str)
{
	int		*counters;
	int		i;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 4)
		*is_correct = FALSE;
	else
	{
		if (!is_tuple(str[1], FALSE)
			|| !is_tuple(str[2], FALSE)
			|| !is_tuple(str[3], TRUE))
			*is_correct = FALSE;
		else
			counters[PLA]++;
	}
}

/*
 * 1 - center
 * 2 - normal / orientation
 * 3 - rib length
 * 4 - color
 */
void	check_square_cube(int **counters_ptr, int *is_correct, char **str)
{
	int		*counters;
	int		i;
	double	s1;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 5)
		*is_correct = FALSE;
	else
	{
		s1 = ft_atod(str[3]);
		if (!is_tuple(str[1], FALSE)
			|| !is_tuple(str[2], FALSE)
			|| !is_tuple(str[4], TRUE)
			|| s1 <= 0.0)
			*is_correct = FALSE;
		else if (ft_strequals(str[0], "sq"))
			counters[SQU]++;
		else
			counters[CUB]++;
	}
}

/*
 * 1 - point A
 * 2 - point B
 * 3 - point C
 * 4 - color
 */
void	check_triangle(int **counters_ptr, int *is_correct, char **str)
{
	int		*counters;
	int		i;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 5)
		*is_correct = FALSE;
	else
	{
		if (!is_tuple(str[1], FALSE)
			|| !is_tuple(str[2], FALSE)
			|| !is_tuple(str[3], FALSE)
			|| !is_tuple(str[4], TRUE))
			*is_correct = FALSE;
		else
			counters[TRI]++;
	}
}

/*
 * 1 - circle center
 * 2 - up vector
 * 3 - height
 * 4 - diameter
 * 5 - color
 */
void	check_cone_cylinder(int **counters_ptr, int *is_correct, char **str)
{
	int		*counters;
	int		i;
	double	s1;
	double	s2;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 6)
		*is_correct = FALSE;
	else
	{
		s1 = ft_atod(str[3]);
		s2 = ft_atod(str[4]);
		if (!is_tuple(str[1], FALSE)
			|| !is_tuple(str[2], FALSE)
			|| !is_tuple(str[5], TRUE)
			|| s1 <= 0.0 || s2 <= 0.0)
			*is_correct = FALSE;
		else if (ft_strequals(str[0], "co"))
			counters[CON]++;
		else
			counters[CYL]++;
	}
}
