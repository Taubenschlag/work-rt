/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 02:59:12 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H
# include "../../../../heads_global/minirt.h"

typedef struct t_square
{
	s_triangle	*t1;
	s_triangle	*t2;
}	s_square;

s_square	*square(void);
s_tuple		*square_normale_at(void);
void		free_square(s_square *t);

#endif //RT_CHALLENGE_SQUARE_H
