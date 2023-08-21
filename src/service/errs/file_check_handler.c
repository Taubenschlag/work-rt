/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 00:51:23 by rokupin           #+#    #+#             */
/*   Updated: 2023/08/21 16:16:26 by sbocanci         ###   ########.fr       */
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

int	*make_counters_array(void)
{
	int	*counters;
	int	i;

	i = -1;
	counters = malloc(sizeof(int) * INSTRUCTION_SET_SIZE);
	while (++i < INSTRUCTION_SET_SIZE)
		counters[i] = 0;
	return (counters);
}

void	cleanup_arr(char **values)
{
	int	i;

	i = -1;
	while (values[++i])
		free(values[i]);
	free(values);
}

void	check_row(int *correct, char **line, char ***values, int *entry)
{
	if (*correct)
	{
		*values = ft_whitespaces(*line);
		if (*values && **values)
			instruction_switch(*values, &entry, correct);
		cleanup_arr(*values);
	}
	free(*line);
}

int	*check_file(char *filename)
{
	int		fd;
	char	*line;
	char	**values;
	int		*entry;
	int		correct;

	/* this might be the second time to open file */
	fd = open(filename, O_RDONLY);
	entry = make_counters_array();
	correct = TRUE;
	while (get_next_line(fd, &line))
		check_row(&correct, &line, &values, entry);
	check_row(&correct, &line, &values, entry);
	close(fd);
	if (!correct || entry[RES] != 1 || entry[AMB] > 1 || entry[CAM] < 1)
	{
		free(entry);
		entry = NULL;
	}
	return (entry);
}
