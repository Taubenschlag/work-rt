/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/02 18:08:16 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

static void	instruction_switch(char **str, int **counters_ptr, int *correct)
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

static void	check_row(int *correct, char *line, char ***values, int *entry)
{
	if (*correct)
	{
		if (find_first('#', line) == 0)
			return ;
		else if (find_first('#', line) > 0)
			line[find_first('#', line)] = '\0';
		*values = ft_whitespaces(line);
		if (*values && **values)
			instruction_switch(*values, &entry, correct);
		cleanup(*values);
	}
}

static void	init_counters_array(int *counters)
{
	int	i;

	i = 0;
	while (i < INSTRUCTION_SET_SIZE)
	{
		counters[i++] = 0;
	}
}

/* 
** input file is opened here one more time to validate the data before parsing
** it is necessary since we use GNL in parse_scene()
** we wont be able to read() from the same fd twice
*/
static bool	check_file(t_scene *s)
{
	int		fd;
	char	line[GNL_BUF_SIZE];
	char	**values;
	int		correct;

	values = NULL;
	correct = 1;
	init_counters_array(s->counters);
	fd = open(s->filename, O_RDONLY);
	if (fd < 0)
		return (false);
	while (get_next_line(fd, line))
		check_row(&correct, line, &values, s->counters);
	check_row(&correct, line, &values, s->counters);
	close(fd);
	if (!correct || s->counters[RES] != 1 || s->counters[AMB] > 1
		|| s->counters[CAM] < 1)
	{
		printf("Error: incorrect input data in '%s'\n", s->filename);
		return (false);
	}
	return (true);
}

bool	check_arguments(t_scene *s, int ac, char **av)
{
	s->fd_infile = -1;
	s->filename = NULL;
	if (ac == 3 || ac == 2)
	{
		s->filename = av[ac - 1];
		s->fd_infile = open(s->filename, O_RDONLY);
	}
	if (s->fd_infile < 0)
	{
		printf("Error: can't open the file '%s'.\n", av[ac - 1]);
		return (false);
	}
	if (ac < 2 || ac > 3
		|| (ac == 3 && !((ft_strequals(av[1], "--save")))))
	{
		printf("Error: wrorg arguments.\n");
		printf("Usage:\n\t./miniRT resources/../'file'.rt\n");
		printf("\t./miniRT --save resources/../'file'.rt\n");
		return (false);
	}
	return (check_file(s));
}
