/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_instructions_checker.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:01:47 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/13 21:31:48 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

/*
 * 1 - height
 * 2 - width
 */
void	check_resolution(int **counters_ptr, int *is_correct, char **str)
{
	int	*counters;
	int	i;
	int	s1;
	int	s2;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 3 || !ft_isnumber(str[1]) || !ft_isnumber(str[2]))
		*is_correct = FALSE;
	else
	{
		s1 = ft_atoi(str[1]);
		s2 = ft_atoi(str[2]);
		if (s1 > 0 && s2 > 0)
			counters[RES]++;
		else
			*is_correct = FALSE;
	}
}

/*
 * 1 - intensity
 * 2 - color
 */
void	check_ambiance(int **counters_ptr, int *is_correct, char **str)
{
	int		*counters;
	int		i;
	double	s1;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 3 || !ft_isdouble(str[1]))
		*is_correct = FALSE;
	else
	{
		s1 = ft_atod(str[1]);
		if (s1 >= 0 && s1 <= 1 && is_tuple(str[2], TRUE))
			counters[AMB]++;
		else
			*is_correct = FALSE;
	}
}

/*
 * 1 - point FROM
 * 2 - vector TO
 * 3 - vector UP
 * 4 - angle
 */
void	check_cameras(int **counters_ptr, int *is_correct, char **str)
{
	int		*counters;
	int		i;
	double	s1;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 5 || !ft_isdouble(str[4]))
		*is_correct = FALSE;
	else
	{
		s1 = ft_atod(str[4]);
		if (!is_tuple(str[1], FALSE)
			|| !is_tuple(str[2], FALSE)
			|| !is_tuple(str[3], FALSE)
			|| s1 <= 0.0)
			*is_correct = FALSE;
		else
			counters[CAM]++;
	}
}

/*
 * 1 - position
 * 2 - intensity
 * 3 - color
 */
void	check_lights(int **counters_ptr, int *is_correct, char **str)
{
	int		*counters;
	int		i;
	double	s1;

	counters = *counters_ptr;
	i = 0;
	while (str[i])
		i++;
	if (i != 4 || !ft_isdouble(str[2]))
		*is_correct = FALSE;
	else
	{
		s1 = ft_atod(str[2]);
		if (!is_tuple(str[1], FALSE)
			|| !is_tuple(str[3], TRUE)
			|| s1 <= 0.0)
			*is_correct = FALSE;
		else
			counters[LHT]++;
	}
}
