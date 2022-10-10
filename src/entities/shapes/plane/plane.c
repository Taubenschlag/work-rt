/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 17:46:48 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../heads_global/minirt.h"

s_plane	*plane_plane(void)
{
	s_plane	*plane;

	plane = (s_plane *)malloc(sizeof(s_plane));
	return (plane);
}

s_plane	*plane_defautl(void)
{
	return (plane_plane());
}

s_tuple	*plane_normal_at(void)
{
	return (tuple_vector(0, 1, 0));
}

void	plane_free(s_plane *pl)
{
	free(pl);
}
