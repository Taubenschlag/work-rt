/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/11 15:45:34 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "../../../../heads_global/minirt.h"

typedef struct cylinder
{
	double		min;
	double		max;
	int			closed;

	t_tuple		*center;
	t_tuple		*norm;
	t_tuple		*color;
	//t_matrix	*trans;
	t_matrix	trans;
	double		d;

	double		a;
	double		b;
	double		c;
	double		disc;
}	t_cylinder;

t_cylinder	*cylinder_cylinder(void);
t_cylinder	*cylinder_params(double h);
t_tuple		*cylinder_normale_at(t_tuple *t, t_cylinder *c);
int			check_cap(t_ray *r, double t);
void		cylinder_free(t_cylinder *c);

#endif
