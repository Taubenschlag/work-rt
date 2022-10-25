/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/16 23:38:48 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads_global/minirt.h"

int	main(int ac, char **av)
{
	int		fd;
	t_scene	s;
	int		*counters;

	fd = check_arguments(ac, av);
	if (fd < 1 || ac < 2 || ac > 3)
		exit(EXIT_FAILURE);
	counters = check_file(av[ac - 1]);
	if (!counters)
		exit(EXIT_FAILURE);
	init_scene(counters, &s);
	if (!parse_scene(fd, counters, &s))
	{
		free_scene(&s);
		perror("invalid file");
		exit(EXIT_FAILURE);
	}
	if (ac == 3)
		save_scene(&s);
	else
		display_scene(&s);
	return (0);
}
