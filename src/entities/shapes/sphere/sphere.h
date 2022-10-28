/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 03:04:08 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include "../../../../heads_global/minirt.h"

typedef struct sphere
{
	t_tuple	*centre;
}	t_sphere;

t_tuple		*nsphere_normal_at(t_tuple *p, t_matrix *m);
t_sphere	*nsphere_nsphere(t_tuple *centre);
t_sphere	*nsphere_unit(t_tuple *centre);
void		nsphere_free(t_sphere *s);

#endif
