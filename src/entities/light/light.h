/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 03:21:41 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "../../../heads_global/minirt.h"

typedef struct t_light
{
	s_tuple	*position;
	s_tuple	*color;
}	s_light;

s_light	*light_make(s_tuple *position, s_tuple *color);
void	light_free(s_light *l);

#endif
