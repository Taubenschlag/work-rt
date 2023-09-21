/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/21 18:26:41 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H
# include "../../../../heads_global/minirt.h"

typedef struct cone
{
	double		min;
	double		max;
	int			closed;

	t_tuple		center;
	t_tuple		norm;
	t_tuple		color;
	t_matrix	trans;
	double		d;

	double		a;
	double		b;
	double		c;
	double		disc;
}	t_cone;

t_cone		*cone_cone(void);
t_cone		*cone_param(double h);
void		cone_normale_at(t_tuple *res, t_tuple *t, t_cone *c);
int			check_cap_cone_max(t_ray *r, double t, double max);
int			check_cap_cone_min(t_ray *r, double t, double min);

#endif
