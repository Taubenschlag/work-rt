/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exceptions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 01:37:13 by rokupin          ###   ########.fr       */
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

void	figure_switch(char *str, int **counters_ptr, int *correct)
{
	int	*counters;

	counters = *counters_ptr;
	if (ft_strequals(str, "R"))
		counters[0]++;
	else if (ft_strequals(str, "A"))
		counters[1]++;
	else if (ft_strequals(str, "c"))
		counters[2]++;
	else if (ft_strequals(str, "l"))
		counters[3]++;
	else if (ft_strequals(str, "sp")
		|| ft_strequals(str, "pl")
		|| ft_strequals(str, "sq")
		|| ft_strequals(str, "cy")
		|| ft_strequals(str, "tr")
		|| ft_strequals(str, "co")
		|| ft_strequals(str, "cu"))
		counters[4]++;
	else
		*correct = 0;
}

int	*make_counters_array(void)
{
	int	*counters;
	int	i;

	i = -1;
	counters = malloc(sizeof(int) * 5);
	while (++i < 5)
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

int	* check_file(char *filename)
{
	int		fd;
	char	*line;
	char	**values;
	int		*counters;
	int		correct;

	fd = open(filename, O_RDONLY);
	counters = make_counters_array();
  	correct = 1;
	while (correct && get_next_line(fd, &line))
	{
		values = ft_whitespaces(line);
		free(line);
		figure_switch(values[0], &counters, &correct);
		cleanup_arr(values);
	}
	free(line);
	close(fd);
	if (!correct || counters[0] != 1 || counters[1] > 1 || counters[2] < 1)
	{
		free(counters);
		perror("invalid file");
		return (NULL);
	}
	return (counters);
}
