/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 03:23:48 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

s_light	*light_make(s_tuple *position, s_tuple *color)
{
	s_light	*ret;

	ret = (s_light *)malloc(sizeof(s_light));
	ret->position = position;
	ret->color = color;
	return (ret);
}

void	light_free(s_light *l)
{
	tuple_free(l->position);
	tuple_free(l->color);
	free(l);
}
