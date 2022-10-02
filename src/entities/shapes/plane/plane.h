/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 03:07:04 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H
# include "../../../../heads_global/minirt.h"

typedef struct t_plane
{
}	s_plane;

s_plane	*plane_plane(void);
s_plane	*plane_defautl(void);
s_tuple	*plane_normal_at(void);
void	plane_free(s_plane *pl);

#endif //RT_CHALLENGE_PLANE_H
