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

typedef struct square
{
	t_triangle	*t1;
	t_triangle	*t2;

	t_tuple		*center;
	t_tuple		*norm;
	t_tuple		*color;
	t_matrix	*trans;
	double		side;
}	t_square;

t_square	*square(void);
t_tuple		*square_normale_at(void);
void		free_square(t_square *t);

#endif //RT_CHALLENGE_SQUARE_H
