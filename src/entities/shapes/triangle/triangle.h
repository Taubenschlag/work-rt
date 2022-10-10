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

typedef struct triangle
{
	t_tuple	*a;
	t_tuple	*b;
	t_tuple	*c;
	t_tuple	*e1;
	t_tuple	*e2;
	t_tuple	*n;

}	t_triangle;

t_triangle	*triangle_coordinates(t_tuple *a, t_tuple *b, t_tuple *c);
t_tuple		*triangle_normale_at(t_triangle *t);
void		free_triangle(t_triangle *t);

#endif //RT_CHALLENGE_TRIANGLE_H
