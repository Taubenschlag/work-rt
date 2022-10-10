/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 21:22:51 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads_global/minirt.h"

/*
 *   counters - filled while checking the input file.
 *   5 position array
 *   [0] - resolution (no more than 1)
 *   [1] - Ambient light (no more than 1)
 *   [2] - Camera (N)
 *   [3] - lights
 *   [4] - Shapes
*/

int	main(int ac, char **av)
{
	int		fd;
	s_scene	*s;
	int		*counters;

	s = NULL;
	fd = check_arguments(ac, av);
	if(fd < 1)
		exit(EXIT_FAILURE);
	counters = check_file(ac == 2? av[1]:av[2]);
	if (!counters)
		exit(EXIT_FAILURE);
	parse_scene(fd, counters, &s);
	free(counters);
	close(fd);
	if (ac == 3)
		save_scene(s);
	else
		display_scene(s);
	return (0);
}
