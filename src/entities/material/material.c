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
t_matrl	*material_make(
		t_tuple *color,
		double diffuse,
		double ambient,
		double specular,
		double shininess)
{
	t_matrl	*res;

	res = (t_matrl *)malloc(sizeof(t_matrl));
	res->color = color;
	res->ambient = ambient;
	res->diffuse = diffuse;
	res->shininess = shininess;
	res->specular = specular;
	return (res);
}

t_matrl	*material_make_default(void)
{
	return (material_make(
			NULL,
			0.9, 0.1, 0.9, 200));
}

t_matrl	*mat_with_col(t_tuple *color)
{
	return (material_make(
			color,
			0.9, 0.1, 0.9, 200));
}

void	material_free(t_matrl *m)
{
	tuple_free(m->color);
	free(m);
}
