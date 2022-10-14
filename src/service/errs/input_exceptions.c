/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exceptions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/14 22:02:55 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

int	check_arguments(int ac, char **av)
{
	int	fd;

	fd = 0;
	if (ac == 3 || ac == 2)
		fd = open(av[ac - 1], O_RDONLY);
	if (ac < 2 || ac > 3
		|| (ac == 3 && !((ft_strequals(av[1], "--save"))))
		|| !fd)
	{
		perror("wrong argument");
		return (-1);
	}
	if (fd == -1)
	{
		perror("file not found");
		return (-1);
	}
	return (fd);
}

void	figure_switch(char **str, int **counters_ptr, int *correct)
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
	counters = malloc(sizeof(int) * 11);
	while (++i < 11)
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

int	*check_file(char *filename)
{
	int		fd;
	char	*line;
	char	**values;
	int		*entry;
	int		correct;

	fd = open(filename, O_RDONLY);
	entry = make_counters_array();
	correct = TRUE;
	while (correct && get_next_line(fd, &line))
	{
		values = ft_whitespaces(line);
		free(line);
		figure_switch(values, &entry, &correct);
		cleanup_arr(values);
	}
	free(line);
	close(fd);
	if (!correct || entry[RES] != 1 || entry[AMB] > 1 || entry[CAM] < 1)
	{
		free(entry);
		perror("invalid file");
		return (NULL);
	}
	return (entry);
}
