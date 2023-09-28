/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/23 18:17:17 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads_global/minirt.h"

int	main(int ac, char **av)
{
	t_scene	s;

	if (check_arguments(&s, ac, av) == false)
	{
		return (1);	
	}
	if (!init_scene(&s) || !parse_scene(&s))
	{
		close(s.fd_infile);
		free_scene(&s);
		return (1);	
	}
	if (ac == 3)
	{
		if (!create_files(&s))
		{
			free_scene(&s);
			return (1);	
		}
		save_scene(&s, s.fd_list);
	}
	else
		display_scene(&s);
	free_scene(&s);
	return (0);
}

/*
int	main(int ac, char **av)
{
	int		fd;
	int		*fd_list;
	t_scene	s;
	int		counters[INSTRUCTION_SET_SIZE];

	fd = check_arguments(ac, av);
	fd_list = NULL;
	check_fd_argnum(fd, ac);
	check_file(av[ac - 1], counters);
	check_counters(counters);
	if (ac == 3)
	{
		fd_list = create_files(counters);
		check_file_creation(fd_list);
	}
	init_scene(counters, &s);
	parse_scene(fd, &s);
	if (ac == 3)
		save_scene(&s, fd_list);
	else
		display_scene(&s);
	return (0);
}
*/