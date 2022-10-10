/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 03:10:52 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "../../../../heads_global/minirt.h"

typedef struct cylinder
{
	double	min;
	double	max;
	int		closed;
}	t_cylinder;

t_cylinder	*cylinder_cylinder(void);
t_cylinder	*cylinder_params(double h);
t_tuple		*cylinder_normale_at(t_tuple *t, t_cylinder *c);
int			check_cap(t_ray *r, double t);
void		cylinder_free(t_cylinder *c);

#endif //RT_CHALLENGE_CYLINDER_H
