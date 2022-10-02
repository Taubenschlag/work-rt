/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/01 02:34:23 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H
# include "../../../heads_global/minirt.h"

typedef struct t_shape
{
	char		type;
	s_matrl		*matrl;
	s_matrix	*trans;
	void		*shape;
}	s_shape;

// static unsigned int g_id;

s_shape	*make_shape(char type, void *shape_itself);
s_shape	*test_shape(void);
void	*set_transform(s_shape *sh, s_matrix *trans);//todo deprecated
s_tuple	*shape_normal_at(s_shape *sh, s_tuple *p);
void	free_shape(s_shape *s);

#endif