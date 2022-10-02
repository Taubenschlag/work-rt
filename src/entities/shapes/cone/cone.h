/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 21:58:58 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H
# include "../../../../heads_global/minirt.h"

typedef struct t_cone
{
	double	min;
	double	max;
	int		closed;
}	s_cone;

s_cone		*cone_cone(void);
s_cone		*cone_param(double h);
s_tuple		*cone_normale_at(s_tuple *t, s_cone *c);
int			check_cap_cone_max(s_ray *r, double t, double max);
int			check_cap_cone_min(s_ray *r, double t, double min);

#endif //RT_CHALLENGE_CONE_H
