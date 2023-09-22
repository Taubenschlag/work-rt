/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:51:23 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/22 10:44:36 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	instruction_switch(char **str, int **counters_ptr, int *correct)
{
	if (ft_strequals(str[0], "R"))
		check_resolution(counters_ptr, correct, str);
	else if (ft_strequals(str[0], "A"))
		check_ambiance(counters_ptr, correct, str);
	else if (ft_strequals(str[0], "c"))
		check_cameras(counters_ptr, correct, str);
	else if (ft_strequals(str[0], "l"))
		check_lights(counters_ptr, correct, str);
	else if (ft_strequals(str[0], "sp"))
		check_sphere(counters_ptr, correct, str);
	else if (ft_strequals(str[0], "pl"))
		check_plane(counters_ptr, correct, str);
	else if (ft_strequals(str[0], "sq") || ft_strequals(str[0], "cu"))
		check_square_cube(counters_ptr, correct, str);
	else if (ft_strequals(str[0], "tr"))
		check_triangle(counters_ptr, correct, str);
	else if (ft_strequals(str[0], "co") || ft_strequals(str[0], "cy"))
		check_cone_cylinder(counters_ptr, correct, str);
	else
		*correct = 0;
}

void	init_counters_array(int *counters)
{
	int	i;

	i = 0;
	while (i < INSTRUCTION_SET_SIZE)
	{
		counters[i++] = 0;
	}
}

void	cleanup_arr(char **values)
{
	int	i;

	i = -1;
	while (values[++i])
		free(values[i]);
	free(values);
}

void	check_row(int *correct, char *line, char ***values, int *entry)
{
	if (*correct)
	{
		*values = ft_whitespaces(line);
		if (*values && **values)
			instruction_switch(*values, &entry, correct);
		cleanup_arr(*values);
	}
}

bool	check_file(char *filename, int *count)
{
	int		fd;
	char	line[GNL_BUF_SIZE];
	char	**values;
	int		correct;

	values = NULL;
	correct = TRUE;
	/* this might be the second time to open file */
	fd = open(filename, O_RDONLY);
	init_counters_array(count);
	while (get_next_line(fd, line))
		check_row(&correct, line, &values, count);
	check_row(&correct, line, &values, count);
	close(fd);
	if (!correct || count[RES] != 1 || count[AMB] > 1 || count[CAM] < 1)
	{
		return (false);
	}
	return (correct);
}
