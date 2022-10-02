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
// TODO mre than 4 args
s_matrl	*material_make(
		s_tuple *color,
		double diffuse,
		double ambient,
		double specular,
		double shininess)
{
	s_matrl	*res;

	res = (s_matrl *)malloc(sizeof(s_matrl));
	res->color = color;
	res->ambient = ambient;
	res->diffuse = diffuse;
	res->shininess = shininess;
	res->specular = specular;
	return (res);
}

s_matrl	*material_make_default(void)
{
	return (material_make(
			NULL,
			0.9, 0.1, 0.9, 200));
}

s_matrl	*mat_with_col(s_tuple *color)
{
	return (material_make(
			color,
			0.9, 0.1, 0.9, 200));
}

void	material_free(s_matrl *m)
{
	tuple_free(m->color);
	free(m);
}
