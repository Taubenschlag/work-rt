/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 19:55:05 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include "../../../../heads_global/minirt.h"

typedef struct sphere
{
	t_tuple	centre;
}	t_sphere;

void		nsphere_normal_at(t_tuple *res, t_tuple *p, t_matrix *m, t_tmp_m *m_tmp);
t_sphere	*nsphere_nsphere(t_tuple *centre);
t_sphere	*nsphere_unit(t_tuple *centre);
void		nsphere_free(t_sphere *s);

#endif
