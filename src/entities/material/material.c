/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 03:14:15 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

t_matrl	*mat_with_col(t_tuple *color)
{
	t_matrl	*res;

	res = (t_matrl *)malloc(sizeof(t_matrl));
	res->color = color;
	res->ambient = 0.1;
	res->diffuse = 0.9;
	res->shininess = 200;
	res->specular = 0.9;
	return (res);
}

void	material_free(t_matrl *m)
{
	tuple_free(m->color);
	free(m);
}
