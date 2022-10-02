/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/09/30 21:32:46 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads_global/minirt.h"

int	main(int ac, char **av)
{
	int		fd;
	s_scene	*s;
	int		*counters;
// TODO fd inside if
	if((fd = check_arguments(ac, av)) < 1 || !(counters = check_file(ac == 2? av[1]:av[2])))
		exit(EXIT_FAILURE);
	else
		s = parse_scene(fd, counters);
	free(counters);
	close(fd);
	if (ac == 3)
		save_scene(s);
	else
		display_scene(s);
	return (0);
}
