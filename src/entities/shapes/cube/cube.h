/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 21:47:43 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "../../../../heads_global/minirt.h"

typedef struct t_cube
{
}	s_cube;

s_cube	*cube_cube(void);
void	cube_free(s_cube *c);
s_tuple	*cube_normal_at(s_tuple *p);

#endif //RT_CHALLENGE_CUBE_H
