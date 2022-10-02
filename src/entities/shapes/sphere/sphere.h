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

typedef struct t_nsphere
{
	s_tuple	*centre;
}	s_nsphere;

s_tuple		*nsphere_normal_at(s_tuple *p, s_matrix *m);
s_nsphere	*nsphere_nsphere(s_tuple *centre);
s_nsphere	*nsphere_unit(s_tuple *centre);
void		nsphere_free(s_nsphere *s);

#endif //RT_CHALLENGE_SPHERE_H
