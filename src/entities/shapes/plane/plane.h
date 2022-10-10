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

typedef struct plane
{
}	plane;

plane	*plane_plane(void);
plane	*plane_defautl(void);
t_tuple	*plane_normal_at(void);
void	plane_free(plane *pl);

#endif //RT_CHALLENGE_PLANE_H
