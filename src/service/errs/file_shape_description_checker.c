/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_shape_description_checker.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:27:33 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 11:34:13 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

/*
 * 1 - centre
 * 2 - diameter
 * 3 - ptrn
 * 4 - color
 */
void	check_sphere(int **counters_ptr, int *is_correct, char **str)
{
	int		*counters;
	int		i;
	double	s1;
	int		s2;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 5 || !ft_isdouble(str[2]) || !ft_isdouble(str[3]))
		*is_correct = FALSE;
	else
	{
		s1 = ft_atod(str[2]);
		s2 = ft_atoi(str[3]);
		if (!is_tuple(str[1], FALSE)
			|| !is_tuple(str[4], TRUE)
			|| s1 <= 0.0
			|| !(s2 == 0 || s2 == 1))
			*is_correct = FALSE;
		else
			counters[SPH]++;
	}
}

/*
 * 1 - point on a t_plane
 * 2 - normale
 * 3 - pattern (size)
 * 4 - color
 */
void	check_plane(int **counters_ptr, int *is_correct, char **str)
{
	int		*counters;
	int		i;
	int		pattern;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 5)
		*is_correct = FALSE;
	else
	{
		pattern = ft_atoi(str[3]);
		if (!is_tuple(str[1], FALSE)
			|| !is_tuple(str[2], FALSE)
			|| !is_tuple(str[4], TRUE)
			|| pattern < 0)
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
	if (i != 5 || !ft_isdouble(str[3]))
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
 * 3 - diameter
 * 4 - height
 * 5 - is closed
 * 6 - color
 */
void	check_cone_cylinder(int **counters_ptr, int *is_correct, char **str)
{
	int		*counters;
	int		i;
	double	s[2];
	int		s3;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 7 || !ft_isdouble(str[3]) || !ft_isdouble(str[4]) \
		|| !ft_isdouble(str[5]))
		*is_correct = FALSE;
	else
	{
		s[0] = ft_atod(str[3]);
		s[1] = ft_atod(str[4]);
		s3 = ft_atoi(str[5]);
		if (!is_tuple(str[1], 0) || !is_tuple(str[2], 0) || !is_tuple(str[6], 1)
			|| s[0] <= 0.0 || s[1] <= 0.0 || !(s3 == 0 || s3 == 1))
			*is_correct = FALSE;
		else if (ft_strequals(str[0], "co"))
			counters[CON]++;
		else
			counters[CYL]++;
	}
}
