/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/11 15:07:09 by sbocanci         ###   ########.fr       */
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
	//t_matrix	*trans;
	t_matrix	trans;
	double		side;
}	t_square;

t_square	*square(void);
t_tuple		*square_normale_at(void);
void		free_square(t_square *t);

#endif
