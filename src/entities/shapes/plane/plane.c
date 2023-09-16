/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/16 21:45:54 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

void	plane_normal_at(t_tuple *t)
{
	tuple_vector(t, 0, 1, 0);
}
/*
t_plane	*plane_plane(void)
{
	t_plane	*new_plane;

	new_plane = (t_plane *)malloc(sizeof(new_plane));
	return (new_plane);
}

t_tuple	*plane_normal_at(void)
{
	return (tuple_vector(0, 1, 0));
}

void	plane_free(t_plane *pl)
{
	free(pl);
}
*/