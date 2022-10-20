/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/18 00:10:25 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

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
