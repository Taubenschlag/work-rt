/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 02:38:50 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H
# include "../../../../heads_global/minirt.h"

typedef struct t_triangle
{
	s_tuple	*a;
	s_tuple	*b;
	s_tuple	*c;
	s_tuple	*e1;
	s_tuple	*e2;
	s_tuple	*n;

}	s_triangle;

s_triangle	*triangle_coordinates(s_tuple *a, s_tuple *b, s_tuple *c);
s_tuple		*triangle_normale_at(s_triangle *t);
void		free_triangle(s_triangle *t);

#endif //RT_CHALLENGE_TRIANGLE_H
