/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 21:58:46 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "../../../heads_global/minirt.h"

typedef struct light
{
	t_tuple	position;
	t_tuple	color;
}	t_light;

void	light_make(t_light *ret, t_tuple *position, t_tuple *color);
void	light_free(t_light *l);

/* DEBUG */
void	print_light(t_light *l);
/* ***** */

#endif
