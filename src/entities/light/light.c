/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 22:01:13 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

/* DEBUG */
void	print_light(t_light *l)
{
	printf("\t\t========================\n");	
	printf("\t\tposition: ");
	print_tuple(&l->position);
	printf("\t\tcolor: ");
	print_tuple(&l->color);
	printf("\t\t= = = = = = = = = = = = =\n");
}
/* ***** */

void	light_free(t_light *l)
{
	free(l);
}

void	light_make(t_light *ret, t_tuple *position, t_tuple *color)
{
	tuple_copy(&ret->position, position);
	tuple_copy(&ret->color, color);
}
