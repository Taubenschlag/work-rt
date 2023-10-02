/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/02 18:04:50 by sbocanci         ###   ########.fr       */
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
		if (!create_files(&s) || !save_scene(&s, s.fd_list))
		{
			free_scene(&s);
			return (1);
		}
	}
	else
		display_scene(&s);
	free_scene(&s);
	return (0);
}
