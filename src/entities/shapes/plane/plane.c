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

plane	*plane_plane(void)
{
	plane	*plane;

	plane = (plane *)malloc(sizeof(plane));
	return (plane);
}

plane	*plane_defautl(void)
{
	return (plane_plane());
}

t_tuple	*plane_normal_at(void)
{
	return (tuple_vector(0, 1, 0));
}

void	plane_free(plane *pl)
{
	free(pl);
}
