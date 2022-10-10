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

typedef struct shape
{
	char		type;
	t_matrl		*matrl;
	t_matrix	*trans;
	void		*shape;
}	t_shape;

// static unsigned int g_id;

t_shape	*make_shape(char type, void *shape_itself);
t_shape	*test_shape(void);
void	*set_transform(t_shape *sh, t_matrix *trans);//todo deprecated
t_tuple	*shape_normal_at(t_shape *sh, t_tuple *p);
void	free_shape(t_shape *s);

#endif